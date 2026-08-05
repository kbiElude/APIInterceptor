/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.4/gl_buffer_storage.h"
#include "OpenGL/globals.h"
#include "OpenGL/state_tracker.h"
#include "OpenGL/utils.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBufferStorage(GLenum      target,
                                         GLsizeiptr  size,
                                         const void* data,
                                         GLbitfield  flags)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glBufferStorage(target=[%s] size=[%d] data=[%p] flags=[%u])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 static_cast<int32_t>(size),
                 data,
                 flags);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBUFFERSTORAGE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_i32       (static_cast<GLint>(size)),
                APIInterceptor::APIFunctionArgument::create_void_ptr  (data),
                APIInterceptor::APIFunctionArgument::create_u32       (flags),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBUFFERSTORAGE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBUFFERSTORAGEPROC>(OpenGL::g_cached_gl_buffer_storage)(target,
                                                                                      size,
                                                                                      data,
                                                                                      flags);

        OpenGL::BufferBindingTarget binding_target;

        if (tracker.is_top_level_api_call                       ()              &&
            OpenGL::Utils::get_buffer_binding_target_for_gl_enum(target,
                                                                &binding_target) )
        {
            auto&        context         = OpenGL::get_context_state();
            const GLuint bound_buffer_id = context.bound_buffers[static_cast<size_t>(binding_target)];

            if (bound_buffer_id != 0)
            {
                auto& buffer_props_ptr = context.buffer_object_id_to_buffer_props_ptr_map[bound_buffer_id];

                if (buffer_props_ptr == nullptr)
                {
                    buffer_props_ptr.reset(new OpenGL::BufferProps() );
                }

                buffer_props_ptr->size_bytes = static_cast<uint32_t>(size);
            }
        }
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBUFFERSTORAGE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
            APIInterceptor::APIFunctionArgument::create_i32       (static_cast<GLint>(size)),
            APIInterceptor::APIFunctionArgument::create_void_ptr  (data),
            APIInterceptor::APIFunctionArgument::create_u32       (flags),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBUFFERSTORAGE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}

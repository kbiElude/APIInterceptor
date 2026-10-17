/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/memory_chunk.h"
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
    APIInterceptor::MemoryChunk             data_chunk(data,
                                                       size,
                                                       sizeof(uint8_t));
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
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
                APIInterceptor::APIFunctionArgument::create_i64          (static_cast<int64_t>(size) ),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(data_chunk.get_id() ),
                APIInterceptor::APIFunctionArgument::create_u32          (flags),
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
            const GLuint bound_buffer_id = context.buffer_manager.get_bound_buffer(binding_target);

            if (bound_buffer_id != 0)
            {
                context.buffer_manager.set_size(bound_buffer_id,
                                                static_cast<uint64_t>(size) );
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
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
            APIInterceptor::APIFunctionArgument::create_i64          (static_cast<int64_t>(size) ),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(data_chunk.get_id() ),
            APIInterceptor::APIFunctionArgument::create_u32          (flags),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBUFFERSTORAGE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}

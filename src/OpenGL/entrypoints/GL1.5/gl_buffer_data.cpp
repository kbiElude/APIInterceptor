/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.5/gl_buffer_data.h"
#include "OpenGL/globals.h"
#include "OpenGL/state_tracker.h"
#include "OpenGL/utils.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBufferData(GLenum      target,
                                      GLsizeiptr  size,
                                      const void* data,
                                      GLenum      usage)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    uint32_t                                data_chunk_id          = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glBufferData(target=[%s] size=[%d] data=[%p] usage=[%s])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 static_cast<uint32_t>(size),
                 data,
                 OpenGL::Utils::get_raw_string_for_gl_enum(usage) );

        /* data may be nullptr when the call is allocation-only (no initial upload). */
        data_chunk_id = APIInterceptor::register_data_chunk(data,
                                                            (data != nullptr) ? static_cast<uint32_t>(size) : 0u);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBUFFERDATA,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
                APIInterceptor::APIFunctionArgument::create_i32          (static_cast<int32_t>(size) ),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(data_chunk_id),
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (usage),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBUFFERDATA,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBUFFERDATAPROC>(OpenGL::g_cached_gl_buffer_data)(target,
                                                                               size,
                                                                               data,
                                                                               usage);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBUFFERDATA,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
            APIInterceptor::APIFunctionArgument::create_i32          (static_cast<int32_t>(size) ),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(data_chunk_id),
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (usage),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBUFFERDATA,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }

    if (tracker.is_top_level_api_call() )
    {
        OpenGL::BufferBindingTarget binding_target;

        if (OpenGL::Utils::get_buffer_binding_target_for_gl_enum(target,
                                                                &binding_target) )
        {
            auto&        context         = OpenGL::get_context_state();
            const GLuint bound_buffer_id = context.bound_buffers    [static_cast<size_t>(binding_target)];

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
}

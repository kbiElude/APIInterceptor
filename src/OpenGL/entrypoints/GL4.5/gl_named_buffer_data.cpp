/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.5/gl_named_buffer_data.h"
#include "OpenGL/globals.h"
#include "OpenGL/state_tracker.h"
#include "OpenGL/utils.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiNamedBufferData(GLuint      buffer,
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

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glNamedBufferData(buffer=[%u] size=[%d] data=[%p] usage=[%s])",
                 buffer,
                 static_cast<int32_t>(size),
                 data,
                 OpenGL::Utils::get_raw_string_for_gl_enum(usage) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLNAMEDBUFFERDATA,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32       (buffer),
                APIInterceptor::APIFunctionArgument::create_i32       (static_cast<GLint>(size) ),
                APIInterceptor::APIFunctionArgument::create_void_ptr  (data),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(usage),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLNAMEDBUFFERDATA,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLNAMEDBUFFERDATAPROC>(OpenGL::g_cached_gl_named_buffer_data)(buffer,
                                                                                          size,
                                                                                          data,
                                                                                          usage);

        if (tracker.is_top_level_api_call() )
        {
            auto& context          = OpenGL::get_context_state();
            auto& buffer_props_ptr = context.buffer_object_id_to_buffer_props_ptr_map[buffer];

            if (buffer_props_ptr == nullptr)
            {
                buffer_props_ptr.reset(new OpenGL::BufferProps() );
            }

            buffer_props_ptr->size_bytes = static_cast<uint32_t>(size);
        }
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLNAMEDBUFFERDATA,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32       (buffer),
            APIInterceptor::APIFunctionArgument::create_i32       (static_cast<GLint>(size) ),
            APIInterceptor::APIFunctionArgument::create_void_ptr  (data),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(usage),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLNAMEDBUFFERDATA,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}

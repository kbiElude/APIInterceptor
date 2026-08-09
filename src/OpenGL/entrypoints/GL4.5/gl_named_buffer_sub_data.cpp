/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.5/gl_named_buffer_sub_data.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiNamedBufferSubData(GLuint      buffer,
                                              GLintptr    offset,
                                              GLsizeiptr  size,
                                              const void* data)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glNamedBufferSubData(buffer=[%u] offset=[%d] size=[%d] data=[%p])",
                 buffer,
                 static_cast<int32_t>(offset),
                 static_cast<int32_t>(size),
                 data);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLNAMEDBUFFERSUBDATA,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32      (buffer),
                APIInterceptor::APIFunctionArgument::create_i32      (static_cast<GLint>(offset) ),
                APIInterceptor::APIFunctionArgument::create_i32      (static_cast<GLint>(size) ),
                APIInterceptor::APIFunctionArgument::create_void_ptr (data),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLNAMEDBUFFERSUBDATA,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLNAMEDBUFFERSUBDATAPROC>(OpenGL::g_cached_gl_named_buffer_sub_data)(buffer,
                                                                                                 offset,
                                                                                                 size,
                                                                                                 data);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLNAMEDBUFFERSUBDATA,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32      (buffer),
            APIInterceptor::APIFunctionArgument::create_i32      (static_cast<GLint>(offset) ),
            APIInterceptor::APIFunctionArgument::create_i32      (static_cast<GLint>(size) ),
            APIInterceptor::APIFunctionArgument::create_void_ptr (data),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLNAMEDBUFFERSUBDATA,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}

/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_scissor.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiScissor(GLint   x,
                                   GLint   y,
                                   GLsizei width,
                                   GLsizei height)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;

    AI_TRACE("glScissor(x=[%d] y=[%d] width=[%d] height=[%d])",
             x,
             y,
             static_cast<int32_t>(width),
             static_cast<int32_t>(height) );

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLSCISSOR,
                                                     &callback_func_ptr,
                                                     &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32(x),
            APIInterceptor::APIFunctionArgument::create_i32(y),
            APIInterceptor::APIFunctionArgument::create_i32(width),
            APIInterceptor::APIFunctionArgument::create_i32(height),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLSCISSOR,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLSCISSORPROC>(g_cached_gl_scissor)(x,
                                                                y,
                                                                width,
                                                                height);
    }
}
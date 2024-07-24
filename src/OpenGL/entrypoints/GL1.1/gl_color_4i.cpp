/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor4i(GLint red,
                                   GLint green,
                                   GLint blue,
                                   GLint alpha)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glaiColor4i(red=[%d] green=[%d] blue=[%d] alpha=[%d])",
             red,
             green,
             blue,
             alpha);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOLOR4I,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32(red),
            APIInterceptor::APIFunctionArgument::create_i32(green),
            APIInterceptor::APIFunctionArgument::create_i32(blue),
            APIInterceptor::APIFunctionArgument::create_i32(alpha),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOLOR4I,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    reinterpret_cast<PFNGLCOLOR4IPROC>(OpenGL::g_cached_gl_color_4i)(red,
                                                                     green,
                                                                     blue,
                                                                     alpha);
}
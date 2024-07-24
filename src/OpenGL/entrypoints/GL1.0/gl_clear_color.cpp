/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_clear_color.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiClearColor(GLfloat red,
                                      GLfloat green,
                                      GLfloat blue,
                                      GLfloat alpha)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glClearColor(red=[%.4f] green=[%.4f] blue=[%.4f] alpha=[%.4f])",
             red,
             green,
             blue,
             alpha);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCLEARCOLOR,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_fp32(red),
            APIInterceptor::APIFunctionArgument::create_fp32(green),
            APIInterceptor::APIFunctionArgument::create_fp32(blue),
            APIInterceptor::APIFunctionArgument::create_fp32(alpha),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCLEARCOLOR,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    if (OpenGL::g_cached_gl_clear_color == nullptr)
    {
        OpenGL::g_cached_gl_clear_color = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glClearColor");
    }

    reinterpret_cast<PFNGLCLEARCOLORPROC>(OpenGL::g_cached_gl_clear_color)(red,
                                                                           green,
                                                                           blue,
                                                                           alpha);
}
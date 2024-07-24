/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor3i(GLint red,
                                   GLint green,
                                   GLint blue)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glColor3i(red=[%d] green=[%d] blue=[%d])",
             red,
             green,
             blue);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOLOR3I,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32(red),
            APIInterceptor::APIFunctionArgument::create_i32(green),
            APIInterceptor::APIFunctionArgument::create_i32(blue),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOLOR3I,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    reinterpret_cast<PFNGLCOLOR3IPROC>(OpenGL::g_cached_gl_color_3i)(red,
                                                                     green,
                                                                     blue);
}
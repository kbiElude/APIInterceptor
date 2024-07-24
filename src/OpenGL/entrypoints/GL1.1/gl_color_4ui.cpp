/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4ui.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor4ui(GLuint red,
                                    GLuint green,
                                    GLuint blue,
                                    GLuint alpha)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glColor4ui(red=[%d] green=[%d] blue=[%d] alpha=[%d])",
             red,
             green,
             blue,
             alpha);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOLOR4UI,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(red),
            APIInterceptor::APIFunctionArgument::create_u32(green),
            APIInterceptor::APIFunctionArgument::create_u32(blue),
            APIInterceptor::APIFunctionArgument::create_u32(alpha),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOLOR4UI,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    reinterpret_cast<PFNGLCOLOR4UIPROC>(OpenGL::g_cached_gl_color_4ui)(red,
                                                                       green,
                                                                       blue,
                                                                       alpha);
}
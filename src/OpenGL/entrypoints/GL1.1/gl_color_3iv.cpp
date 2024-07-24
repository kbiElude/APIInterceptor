/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor3iv(const GLint* v)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glColor3iv(v=[%p])",
             v);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOLOR3IV,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32_ptr(v),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOLOR3IV,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    reinterpret_cast<PFNGLCOLOR3IVPROC>(OpenGL::g_cached_gl_color_3iv)(v);
}
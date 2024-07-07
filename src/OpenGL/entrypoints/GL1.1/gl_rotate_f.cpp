/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_rotate_f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRotatef(GLfloat angle,
                                   GLfloat x,
                                   GLfloat y,
                                   GLfloat z)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glRotatef(angle=[%.4f], x=[%.4f], y=[%.4f], z=[%.4f])",
             angle,
             x,
             y,
             z);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLACCUM,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_fp32(angle),
            APIInterceptor::APIFunctionArgument::create_fp32(x),
            APIInterceptor::APIFunctionArgument::create_fp32(y),
            APIInterceptor::APIFunctionArgument::create_fp32(z)
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLROTATEF,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    reinterpret_cast<PFNGLROTATEFPROC>(OpenGL::g_cached_gl_rotate_f)(angle,
                                                                     x,
                                                                     y,
                                                                     z);
}
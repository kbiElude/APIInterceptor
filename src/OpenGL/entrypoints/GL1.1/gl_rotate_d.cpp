/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_rotate_d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRotated(GLdouble angle,
                                   GLdouble x,
                                   GLdouble y,
                                   GLdouble z)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;

    AI_TRACE("glRotated(angle=[%.4lf], x=[%.4lf], y=[%.4lf], z=[%.4lf])",
             angle,
             x,
             y,
             z);

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLROTATED,
                                                     &callback_func_ptr,
                                                     &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_fp64(angle),
            APIInterceptor::APIFunctionArgument::create_fp64(x),
            APIInterceptor::APIFunctionArgument::create_fp64(y),
            APIInterceptor::APIFunctionArgument::create_fp64(z),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLROTATED,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLROTATEDPROC>(OpenGL::g_cached_gl_rotate_d)(angle,
                                                                         x,
                                                                         y,
                                                                         z);
    }
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_4d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex4d(GLdouble x,
                                    GLdouble y,
                                    GLdouble z,
                                    GLdouble w)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glVertex4d(x=[%.4lf], y=[%.4lf], z=[%.4lf], w=[%.4lf])",
             x,
             y,
             z,
             w);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEX4D,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_fp64(x),
            APIInterceptor::APIFunctionArgument::create_fp64(y),
            APIInterceptor::APIFunctionArgument::create_fp64(z),
            APIInterceptor::APIFunctionArgument::create_fp64(w),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEX4D,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLVERTEX4DPROC>(OpenGL::g_cached_gl_vertex_4d)(x,
                                                                           y,
                                                                           z,
                                                                           w);
    }
}
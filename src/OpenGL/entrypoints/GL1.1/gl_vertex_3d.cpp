/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_3d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex3d(GLdouble x,
                                    GLdouble y,
                                    GLdouble z)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glVertex3d(x=[%.4lf], y=[%.4lf], z=[%.4lf])",
                 x,
                 y,
                 z);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEX3D,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_fp64(x),
                APIInterceptor::APIFunctionArgument::create_fp64(y),
                APIInterceptor::APIFunctionArgument::create_fp64(z),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEX3D,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLVERTEX3DPROC>(OpenGL::g_cached_gl_vertex_3d)(x,
                                                                           y,
                                                                           z);
    }
}
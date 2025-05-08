/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_4d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord4d(GLdouble s,
                                      GLdouble t,
                                      GLdouble r,
                                      GLdouble q)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glTexCoord4d(s=[%.4lf], t=[%.4lf], r=[%.4lf], q=[%.4lf])",
                 s,
                 t,
                 r,
                 q);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXCOORD4D,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_fp64(s),
                APIInterceptor::APIFunctionArgument::create_fp64(t),
                APIInterceptor::APIFunctionArgument::create_fp64(r),
                APIInterceptor::APIFunctionArgument::create_fp64(q),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXCOORD4D,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXCOORD4DPROC>(OpenGL::g_cached_gl_tex_coord_4d)(s,
                                                                                t,
                                                                                r,
                                                                                q);
    }
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_frustum.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFrustum(GLdouble left,
                                   GLdouble right,
                                   GLdouble bottom,
                                   GLdouble top,
                                   GLdouble zNear,
                                   GLdouble zFar)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glFrustum(left=[%.4lf], right=[%.4lf] bottom=[%.4lf] top=[%.4lf] zNear=[%.4lf] zFar=[%.4lf])",
             left,
             right,
             bottom,
             top,
             zNear,
             zFar);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLFRUSTUM,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_fp64(left),
            APIInterceptor::APIFunctionArgument::create_fp64(right),
            APIInterceptor::APIFunctionArgument::create_fp64(bottom),
            APIInterceptor::APIFunctionArgument::create_fp64(top),
            APIInterceptor::APIFunctionArgument::create_fp64(zNear),
            APIInterceptor::APIFunctionArgument::create_fp64(zFar)
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLFRUSTUM,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLFRUSTUMPROC>(OpenGL::g_cached_gl_frustum)(left,
                                                                        right,
                                                                        bottom,
                                                                        top,
                                                                        zNear,
                                                                        zFar);
    }
}
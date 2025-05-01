/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_pop_matrix.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPopMatrix()
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;

    AI_TRACE("glPopMatrix()");

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPOPMATRIX,
                                                     &callback_func_ptr,
                                                     &callback_func_arg) )
    {
        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPOPMATRIX,
                          0,       /* in_n_args   */
                          nullptr, /* in_args_ptr */
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLPOPMATRIXPROC>(OpenGL::g_cached_gl_pop_matrix)();
    }
}
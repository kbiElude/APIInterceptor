/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_depth_range.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDepthRange(GLdouble n,
                                      GLdouble f)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glDepthRange(n=[%.4f] f=[%.4f])",
             n,
             f);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDEPTHRANGE,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_fp64(n),
            APIInterceptor::APIFunctionArgument::create_fp64(f),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDEPTHRANGE,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDEPTHRANGEPROC>(OpenGL::g_cached_gl_depth_range)(n,
                                                                               f);
    }
}
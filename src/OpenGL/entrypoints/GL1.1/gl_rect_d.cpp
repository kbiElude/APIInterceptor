/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_rect_d.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRectd(GLdouble x1,
                                 GLdouble y1,
                                 GLdouble x2,
                                 GLdouble y2)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glRectd(x1=[%.4lf], y1=[%.4lf], x2=[%.4lf], y2=[%.4lf])",
                 x1,
                 y1,
                 x2,
                 y2);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLRECTD,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_fp64(x1),
                APIInterceptor::APIFunctionArgument::create_fp64(y1),
                APIInterceptor::APIFunctionArgument::create_fp64(x2),
                APIInterceptor::APIFunctionArgument::create_fp64(y2),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLRECTD,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLRECTDPROC>(OpenGL::g_cached_gl_rect_d)(x1,
                                                                     y1,
                                                                     x2,
                                                                     y2);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLRECTD,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_fp64(x1),
            APIInterceptor::APIFunctionArgument::create_fp64(y1),
            APIInterceptor::APIFunctionArgument::create_fp64(x2),
            APIInterceptor::APIFunctionArgument::create_fp64(y2),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLRECTD,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
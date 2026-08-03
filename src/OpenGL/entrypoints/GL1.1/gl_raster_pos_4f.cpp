/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_4f.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos4f(GLfloat x,
                                       GLfloat y,
                                       GLfloat z,
                                       GLfloat w)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glRasterPos4f(x=[%.4lf], y=[%.4lf], z=[%.4lf], w=[%.4lf])",
                 x,
                 y,
                 z,
                 w);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLRASTERPOS4F,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_fp32(x),
                APIInterceptor::APIFunctionArgument::create_fp32(y),
                APIInterceptor::APIFunctionArgument::create_fp32(z),
                APIInterceptor::APIFunctionArgument::create_fp32(w),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLRASTERPOS4F,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLRASTERPOS4FPROC>(OpenGL::g_cached_gl_raster_pos_4f)(x,
                                                                                  y,
                                                                                  z,
                                                                                  w);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLRASTERPOS4F,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_fp32(x),
            APIInterceptor::APIFunctionArgument::create_fp32(y),
            APIInterceptor::APIFunctionArgument::create_fp32(z),
            APIInterceptor::APIFunctionArgument::create_fp32(w),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLRASTERPOS4F,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
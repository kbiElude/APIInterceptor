/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_rect_f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRectf(GLfloat x1,
                                 GLfloat y1,
                                 GLfloat x2,
                                 GLfloat y2)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glRectf(x1=[%.4f], y1=[%.4f], x2=[%.4f], y2=[%.4f])",
                 x1,
                 y1,
                 x2,
                 y2);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLRECTF,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_fp32(x1),
                APIInterceptor::APIFunctionArgument::create_fp32(y1),
                APIInterceptor::APIFunctionArgument::create_fp32(x2),
                APIInterceptor::APIFunctionArgument::create_fp32(y2),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLRECTF,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLRECTFPROC>(OpenGL::g_cached_gl_rect_f)(x1,
                                                                     y1,
                                                                     x2,
                                                                     y2);
    }
}
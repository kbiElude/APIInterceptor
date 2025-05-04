/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_rect_i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRecti(GLint x1,
                                 GLint y1,
                                 GLint x2,
                                 GLint y2)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glRecti(x1=[%d], y1=[%d], x2=[%d], y2=[%d])",
                 x1,
                 y1,
                 x2,
                 y2);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLRECTI,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32(x1),
                APIInterceptor::APIFunctionArgument::create_i32(y1),
                APIInterceptor::APIFunctionArgument::create_i32(x2),
                APIInterceptor::APIFunctionArgument::create_i32(y2),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLRECTI,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLRECTIPROC>(OpenGL::g_cached_gl_rect_i)(x1,
                                                                     y1,
                                                                     x2,
                                                                     y2);
    }
}
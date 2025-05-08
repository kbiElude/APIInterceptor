/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_draw_arrays.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawArrays(GLenum  mode,
                                      GLint   first,
                                      GLsizei count)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glDrawArrays(mode=[%s] first=[%d] count=[%d])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(mode),
                 first,
                 static_cast<int32_t>(count) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWARRAYS,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32(mode),
                APIInterceptor::APIFunctionArgument::create_i32(first),
                APIInterceptor::APIFunctionArgument::create_i32(count),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWARRAYS,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDRAWARRAYSPROC>(OpenGL::g_cached_gl_draw_arrays)(mode,
                                                                               first,
                                                                               count);
    }
}
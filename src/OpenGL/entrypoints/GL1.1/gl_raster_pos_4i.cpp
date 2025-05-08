/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_4i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos4i(GLint x,
                                       GLint y,
                                       GLint z,
                                       GLint w)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glRasterPos4i(x=[%d], y=[%d], z=[%d], w=[%d])",
                 x,
                 y,
                 z,
                 w);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLRASTERPOS4I,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32(x),
                APIInterceptor::APIFunctionArgument::create_i32(y),
                APIInterceptor::APIFunctionArgument::create_i32(z),
                APIInterceptor::APIFunctionArgument::create_i32(w),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLRASTERPOS4I,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLRASTERPOS4IPROC>(OpenGL::g_cached_gl_raster_pos_4i)(x,
                                                                                  y,
                                                                                  z,
                                                                                  w);
    }
}
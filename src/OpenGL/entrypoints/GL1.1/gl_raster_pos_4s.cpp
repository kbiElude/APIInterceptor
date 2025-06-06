/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_4s.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos4s(GLshort x,
                                       GLshort y,
                                       GLshort z,
                                       GLshort w)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glRasterPos4i(x=[%d], y=[%d], z=[%d], w=[%d])",
                 static_cast<int32_t>(x),
                 static_cast<int32_t>(y),
                 static_cast<int32_t>(z),
                 static_cast<int32_t>(w) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLRASTERPOS4S,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i16(x),
                APIInterceptor::APIFunctionArgument::create_i16(y),
                APIInterceptor::APIFunctionArgument::create_i16(z),
                APIInterceptor::APIFunctionArgument::create_i16(w),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLRASTERPOS4S,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLRASTERPOS4SPROC>(OpenGL::g_cached_gl_raster_pos_4s)(x,
                                                                                  y,
                                                                                  z,
                                                                                  w);
    }
}
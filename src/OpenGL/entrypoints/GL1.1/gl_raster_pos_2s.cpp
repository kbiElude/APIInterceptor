/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_2s.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos2s(GLshort x,
                                       GLshort y)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glRasterPos2s(x=[%d] y=[%d])",
             static_cast<int32_t>(x),
             static_cast<int32_t>(y) );

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLRASTERPOS2S,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i16(x),
            APIInterceptor::APIFunctionArgument::create_i16(y),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLRASTERPOS2S,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLRASTERPOS2SPROC>(OpenGL::g_cached_gl_raster_pos_2s)(x,
                                                                                  y);
    }
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_rect_s.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRects(GLshort x1,
                                 GLshort y1,
                                 GLshort x2,
                                 GLshort y2)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glRects(x1=[%d], y1=[%d], x2=[%d], y2=[%d])",
             static_cast<int32_t>(x1),
             static_cast<int32_t>(y1),
             static_cast<int32_t>(x2),
             static_cast<int32_t>(y2) );

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLRECTS,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i16(x1),
            APIInterceptor::APIFunctionArgument::create_i16(y1),
            APIInterceptor::APIFunctionArgument::create_i16(x2),
            APIInterceptor::APIFunctionArgument::create_i16(y2),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLRECTS,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLRECTSPROC>(OpenGL::g_cached_gl_rect_s)(x1,
                                                                     y1,
                                                                     x2,
                                                                     y2);
    }
}
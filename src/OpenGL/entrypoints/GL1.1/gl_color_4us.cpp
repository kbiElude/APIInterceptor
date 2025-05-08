/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4us.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor4us(GLushort red,
                                    GLushort green,
                                    GLushort blue,
                                    GLushort alpha)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glColor4us(red=[%d] green=[%d] blue=[%d] alpha=[%d])",
                 static_cast<uint32_t>(red),
                 static_cast<uint32_t>(green),
                 static_cast<uint32_t>(blue),
                 static_cast<uint32_t>(alpha) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOLOR4US,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u16(red),
                APIInterceptor::APIFunctionArgument::create_u16(green),
                APIInterceptor::APIFunctionArgument::create_u16(blue),
                APIInterceptor::APIFunctionArgument::create_u16(alpha),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOLOR4US,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCOLOR4USPROC>(OpenGL::g_cached_gl_color_4us)(red,
                                                                           green,
                                                                           blue,
                                                                           alpha);
    }
}
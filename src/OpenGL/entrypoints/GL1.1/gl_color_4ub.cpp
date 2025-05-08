/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4ub.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor4ub(GLubyte red,
                                    GLubyte green,
                                    GLubyte blue,
                                    GLubyte alpha)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glColor4ub(red=[%d] green=[%d] blue=[%d] alpha=[%d])",
                 static_cast<uint32_t>(red),
                 static_cast<uint32_t>(green),
                 static_cast<uint32_t>(blue),
                 static_cast<uint32_t>(alpha) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOLOR4UB,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u8(red),
                APIInterceptor::APIFunctionArgument::create_u8(green),
                APIInterceptor::APIFunctionArgument::create_u8(blue),
                APIInterceptor::APIFunctionArgument::create_u8(alpha),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOLOR4UB,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCOLOR4UBPROC>(OpenGL::g_cached_gl_color_4ub)(red,
                                                                           green,
                                                                           blue,
                                                                           alpha);
    }
}
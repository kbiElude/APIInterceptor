/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4b.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor4b(GLbyte red,
                                   GLbyte green,
                                   GLbyte blue,
                                   GLbyte alpha)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glColor4b(red=[%d] green=[%d] blue=[%d] alpha=[%d])",
                 static_cast<uint32_t>(red),
                 static_cast<uint32_t>(green),
                 static_cast<uint32_t>(blue),
                 static_cast<uint32_t>(alpha) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOLOR4B,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i8(red),
                APIInterceptor::APIFunctionArgument::create_i8(green),
                APIInterceptor::APIFunctionArgument::create_i8(blue),
                APIInterceptor::APIFunctionArgument::create_i8(alpha),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOLOR4B,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCOLOR4BPROC>(OpenGL::g_cached_gl_color_4b)(red,
                                                                         green,
                                                                         blue,
                                                                         alpha);
    }
}
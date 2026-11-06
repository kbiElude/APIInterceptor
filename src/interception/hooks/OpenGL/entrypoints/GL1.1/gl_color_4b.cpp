/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/callbacks.h"
#include "common/logger.h"
#include "common/macros.h"
#include "common/tracker.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_4b.h"
#include "interception/hooks/OpenGL/globals.h"
#include "interception/core/OpenGLUtils/utils_enum.h"
#include "interception/hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiColor4b(GLbyte red,
                                                        GLbyte green,
                                                        GLbyte blue,
                                                        GLbyte alpha)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glColor4b(red=[%d] green=[%d] blue=[%d] alpha=[%d])",
                 static_cast<uint32_t>(red),
                 static_cast<uint32_t>(green),
                 static_cast<uint32_t>(blue),
                 static_cast<uint32_t>(alpha) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOLOR4B,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i8(red),
                APIInterceptor::APIFunctionArgument::create_i8(green),
                APIInterceptor::APIFunctionArgument::create_i8(blue),
                APIInterceptor::APIFunctionArgument::create_i8(alpha),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOLOR4B,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCOLOR4BPROC>(Interception::Hooks::OpenGL::g_cached_gl_color_4b)(red,
                                                                                              green,
                                                                                              blue,
                                                                                              alpha);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOLOR4B,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i8(red),
            APIInterceptor::APIFunctionArgument::create_i8(green),
            APIInterceptor::APIFunctionArgument::create_i8(blue),
            APIInterceptor::APIFunctionArgument::create_i8(alpha),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOLOR4B,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
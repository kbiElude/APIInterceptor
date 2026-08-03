/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4ui.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor4ui(GLuint red,
                                    GLuint green,
                                    GLuint blue,
                                    GLuint alpha)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glColor4ui(red=[%d] green=[%d] blue=[%d] alpha=[%d])",
                 red,
                 green,
                 blue,
                 alpha);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOLOR4UI,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32(red),
                APIInterceptor::APIFunctionArgument::create_u32(green),
                APIInterceptor::APIFunctionArgument::create_u32(blue),
                APIInterceptor::APIFunctionArgument::create_u32(alpha),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOLOR4UI,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCOLOR4UIPROC>(OpenGL::g_cached_gl_color_4ui)(red,
                                                                           green,
                                                                           blue,
                                                                           alpha);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOLOR4UI,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(red),
            APIInterceptor::APIFunctionArgument::create_u32(green),
            APIInterceptor::APIFunctionArgument::create_u32(blue),
            APIInterceptor::APIFunctionArgument::create_u32(alpha),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOLOR4UI,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
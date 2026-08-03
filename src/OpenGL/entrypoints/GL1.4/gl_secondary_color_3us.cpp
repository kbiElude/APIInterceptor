/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.4/gl_secondary_color_3us.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiSecondaryColor3us(GLushort red,
                                             GLushort green,
                                             GLushort blue)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glSecondaryColor3us(red=[%u], green=[%u], blue=[%u])",
                 red,
                 green,
                 blue);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLSECONDARYCOLOR3US,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u16(red),
                APIInterceptor::APIFunctionArgument::create_u16(green),
                APIInterceptor::APIFunctionArgument::create_u16(blue),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLSECONDARYCOLOR3US,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLSECONDARYCOLOR3USPROC>(OpenGL::g_cached_gl_secondary_color_3us)(red,
                                                                                              green,
                                                                                              blue);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLSECONDARYCOLOR3US,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u16(red),
            APIInterceptor::APIFunctionArgument::create_u16(green),
            APIInterceptor::APIFunctionArgument::create_u16(blue),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLSECONDARYCOLOR3US,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
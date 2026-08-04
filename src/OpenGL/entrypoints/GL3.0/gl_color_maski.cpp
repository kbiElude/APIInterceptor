/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.0/gl_color_maski.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColorMaski(GLuint    index,
                                      GLboolean r,
                                      GLboolean g,
                                      GLboolean b,
                                      GLboolean a)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glColorMaski(index=[%u] r=[%d] g=[%d] b=[%d] a=[%d])",
                 index,
                 (r == GL_TRUE) ? 1 : 0,
                 (g == GL_TRUE) ? 1 : 0,
                 (b == GL_TRUE) ? 1 : 0,
                 (a == GL_TRUE) ? 1 : 0);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOLORMASKI,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32(index),
                APIInterceptor::APIFunctionArgument::create_u8 (r),
                APIInterceptor::APIFunctionArgument::create_u8 (g),
                APIInterceptor::APIFunctionArgument::create_u8 (b),
                APIInterceptor::APIFunctionArgument::create_u8 (a),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOLORMASKI,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCOLORMASKIPROC>(OpenGL::g_cached_gl_color_maski)(index,
                                                                               r,
                                                                               g,
                                                                               b,
                                                                               a);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOLORMASKI,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(index),
            APIInterceptor::APIFunctionArgument::create_u8 (r),
            APIInterceptor::APIFunctionArgument::create_u8 (g),
            APIInterceptor::APIFunctionArgument::create_u8 (b),
            APIInterceptor::APIFunctionArgument::create_u8 (a),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOLORMASKI,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}

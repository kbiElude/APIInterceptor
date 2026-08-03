/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nub.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib4Nub(GLuint  index,
                                            GLubyte x,
                                            GLubyte y,
                                            GLubyte z,
                                            GLubyte w)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glVertexAttrib4Nub(index=[%u] x=[%u] y=[%u] z=[%u] w=[%u])",
                 index,
                 static_cast<uint32_t>(x),
                 static_cast<uint32_t>(y),
                 static_cast<uint32_t>(z),
                 static_cast<uint32_t>(w) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB4NUB,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32 (index),
                APIInterceptor::APIFunctionArgument::create_u8  (x),
                APIInterceptor::APIFunctionArgument::create_u8  (y),
                APIInterceptor::APIFunctionArgument::create_u8  (z),
                APIInterceptor::APIFunctionArgument::create_u8  (w),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB4NUB,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLVERTEXATTRIB4NUBPROC>(OpenGL::g_cached_gl_vertex_attrib_4Nub)(index,
                                                                                            x,
                                                                                            y,
                                                                                            z,
                                                                                            w);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB4NUB,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32 (index),
            APIInterceptor::APIFunctionArgument::create_u8  (x),
            APIInterceptor::APIFunctionArgument::create_u8  (y),
            APIInterceptor::APIFunctionArgument::create_u8  (z),
            APIInterceptor::APIFunctionArgument::create_u8  (w),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB4NUB,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}

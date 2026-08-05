/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.1/gl_viewport_arrayv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiViewportArrayv(GLuint         first,
                                          GLsizei        count,
                                          const GLfloat* v)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glViewportArrayv(first=[%u] count=[%d] v=[%p])",
                 first,
                 static_cast<int32_t>(count),
                 v);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVIEWPORTARRAYV,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32      (first),
                APIInterceptor::APIFunctionArgument::create_i32      (count),
                APIInterceptor::APIFunctionArgument::create_fp32_ptr (v),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVIEWPORTARRAYV,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLVIEWPORTARRAYVPROC>(OpenGL::g_cached_gl_viewport_arrayv)(first,
                                                                                        count,
                                                                                        v);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVIEWPORTARRAYV,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32      (first),
            APIInterceptor::APIFunctionArgument::create_i32      (count),
            APIInterceptor::APIFunctionArgument::create_fp32_ptr (v),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVIEWPORTARRAYV,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}

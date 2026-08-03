/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_3i.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniform3i(GLint location,
                                     GLint v0,
                                     GLint v1,
                                     GLint v2)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glUniform3i(location=[%d] v0=[%d] v1=[%d] v2=[%d])",
                 location,
                 v0,
                 v1,
                 v2);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLUNIFORM3I,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32(location),
                APIInterceptor::APIFunctionArgument::create_i32(v0),
                APIInterceptor::APIFunctionArgument::create_i32(v1),
                APIInterceptor::APIFunctionArgument::create_i32(v2),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLUNIFORM3I,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLUNIFORM3IPROC>(OpenGL::g_cached_gl_uniform_3i)(location,
                                                                             v0,
                                                                             v1,
                                                                             v2);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLUNIFORM3I,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32(location),
            APIInterceptor::APIFunctionArgument::create_i32(v0),
            APIInterceptor::APIFunctionArgument::create_i32(v1),
            APIInterceptor::APIFunctionArgument::create_i32(v2),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLUNIFORM3I,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}

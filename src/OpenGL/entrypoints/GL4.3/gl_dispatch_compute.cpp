/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_dispatch_compute.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDispatchCompute(GLuint num_groups_x,
                                           GLuint num_groups_y,
                                           GLuint num_groups_z)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glDispatchCompute(num_groups_x=[%u] num_groups_y=[%u] num_groups_z=[%u])",
                 num_groups_x,
                 num_groups_y,
                 num_groups_z);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDISPATCHCOMPUTE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32(num_groups_x),
                APIInterceptor::APIFunctionArgument::create_u32(num_groups_y),
                APIInterceptor::APIFunctionArgument::create_u32(num_groups_z),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDISPATCHCOMPUTE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDISPATCHCOMPUTEPROC>(OpenGL::g_cached_gl_dispatch_compute)(num_groups_x,
                                                                                          num_groups_y,
                                                                                          num_groups_z);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDISPATCHCOMPUTE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(num_groups_x),
            APIInterceptor::APIFunctionArgument::create_u32(num_groups_y),
            APIInterceptor::APIFunctionArgument::create_u32(num_groups_z),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDISPATCHCOMPUTE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}

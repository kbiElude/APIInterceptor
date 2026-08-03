/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_map_grid_1f.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMapGrid1f(GLint   un,
                                     GLfloat u1,
                                     GLfloat u2)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glMapGrid1f(un=[%d], u1=[%.4f], u2=[%.4f])",
                 un,
                 u1,
                 u2);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAPGRID1F,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32 (un),
                APIInterceptor::APIFunctionArgument::create_fp32(u1),
                APIInterceptor::APIFunctionArgument::create_fp32(u2),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAPGRID1F,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLMAPGRID1FPROC>(OpenGL::g_cached_gl_map_grid_1f)(un,
                                                                              u1,
                                                                              u2);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAPGRID1F,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32 (un),
            APIInterceptor::APIFunctionArgument::create_fp32(u1),
            APIInterceptor::APIFunctionArgument::create_fp32(u2),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAPGRID1F,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
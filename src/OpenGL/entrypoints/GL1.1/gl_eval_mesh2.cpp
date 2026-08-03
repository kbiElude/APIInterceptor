/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_eval_mesh2.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEvalMesh2(GLenum mode,
                                     GLint  i1,
                                     GLint  i2,
                                     GLint  j1,
                                     GLint  j2)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glEvalMesh2(mode=[%s], i1=[%d], i2=[%d], j1=[%d], j2=[%d])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(mode),
                 i1,
                 i2,
                 j1,
                 j2);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLEVALMESH2,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(mode),
                APIInterceptor::APIFunctionArgument::create_i32       (i1),
                APIInterceptor::APIFunctionArgument::create_i32       (i2),
                APIInterceptor::APIFunctionArgument::create_i32       (j1),
                APIInterceptor::APIFunctionArgument::create_i32       (j2),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLEVALMESH2,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLEVALMESH2PROC>(OpenGL::g_cached_gl_eval_mesh2)(mode,
                                                                             i1,
                                                                             i2,
                                                                             j1,
                                                                             j2);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLEVALMESH2,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(mode),
            APIInterceptor::APIFunctionArgument::create_i32       (i1),
            APIInterceptor::APIFunctionArgument::create_i32       (i2),
            APIInterceptor::APIFunctionArgument::create_i32       (j1),
            APIInterceptor::APIFunctionArgument::create_i32       (j2),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLEVALMESH2,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
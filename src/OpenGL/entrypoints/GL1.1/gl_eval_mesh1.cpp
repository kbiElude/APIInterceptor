/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_eval_mesh1.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEvalMesh1(GLenum mode,
                                     GLint  i1,
                                     GLint  i2)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glEvalMesh1(mode=[%s], i1=[%d], i2=[%d])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(mode),
                 i1,
                 i2);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLEVALMESH1,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32(mode),
                APIInterceptor::APIFunctionArgument::create_i32(i1),
                APIInterceptor::APIFunctionArgument::create_i32(i2),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLEVALMESH1,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLEVALMESH1PROC>(OpenGL::g_cached_gl_eval_mesh1)(mode,
                                                                             i1,
                                                                             i2);
    }
}
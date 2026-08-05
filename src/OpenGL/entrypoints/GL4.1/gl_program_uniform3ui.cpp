/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.1/gl_program_uniform3ui.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiProgramUniform3ui(GLuint  program,
                                             GLint   location,
                                             GLuint  v0,
                                             GLuint  v1,
                                             GLuint  v2)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glProgramUniform3ui(program=[%u] location=[%d] v0=[%u] v1=[%u] v2=[%u])",
                 program,
                 location,
                 v0,
                 v1,
                 v2);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPROGRAMUNIFORM3UI,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32(program),
                APIInterceptor::APIFunctionArgument::create_i32(location),
                APIInterceptor::APIFunctionArgument::create_u32(v0),
                APIInterceptor::APIFunctionArgument::create_u32(v1),
                APIInterceptor::APIFunctionArgument::create_u32(v2),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPROGRAMUNIFORM3UI,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLPROGRAMUNIFORM3UIPROC>(OpenGL::g_cached_gl_program_uniform3ui)(program,
                                                                                              location,
                                                                                              v0,
                                                                                              v1,
                                                                                              v2);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPROGRAMUNIFORM3UI,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(program),
            APIInterceptor::APIFunctionArgument::create_i32(location),
            APIInterceptor::APIFunctionArgument::create_u32(v0),
            APIInterceptor::APIFunctionArgument::create_u32(v1),
            APIInterceptor::APIFunctionArgument::create_u32(v2),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPROGRAMUNIFORM3UI,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}

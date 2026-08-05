/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.1/gl_program_uniform2d.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiProgramUniform2d(GLuint    program,
                                            GLint     location,
                                            GLdouble  v0,
                                            GLdouble  v1)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glProgramUniform2d(program=[%u] location=[%d] v0=[%f] v1=[%f])",
                 program,
                 location,
                 v0,
                 v1);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPROGRAMUNIFORM2D,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32  (program),
                APIInterceptor::APIFunctionArgument::create_i32  (location),
                APIInterceptor::APIFunctionArgument::create_fp64 (v0),
                APIInterceptor::APIFunctionArgument::create_fp64 (v1),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPROGRAMUNIFORM2D,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLPROGRAMUNIFORM2DPROC>(OpenGL::g_cached_gl_program_uniform2d)(program,
                                                                                            location,
                                                                                            v0,
                                                                                            v1);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPROGRAMUNIFORM2D,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32  (program),
            APIInterceptor::APIFunctionArgument::create_i32  (location),
            APIInterceptor::APIFunctionArgument::create_fp64 (v0),
            APIInterceptor::APIFunctionArgument::create_fp64 (v1),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPROGRAMUNIFORM2D,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}

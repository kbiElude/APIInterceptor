/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.1/gl_program_uniform2uiv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiProgramUniform2uiv(GLuint         program,
                                              GLint          location,
                                              GLsizei        count,
                                              const GLuint*  value)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glProgramUniform2uiv(program=[%u] location=[%d] count=[%d] value=[%p])",
                 program,
                 location,
                 static_cast<int32_t>(count),
                 value);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPROGRAMUNIFORM2UIV,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32     (program),
                APIInterceptor::APIFunctionArgument::create_i32     (location),
                APIInterceptor::APIFunctionArgument::create_i32     (count),
                APIInterceptor::APIFunctionArgument::create_u32_ptr (value),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPROGRAMUNIFORM2UIV,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLPROGRAMUNIFORM2UIVPROC>(OpenGL::g_cached_gl_program_uniform2uiv)(program,
                                                                                                location,
                                                                                                count,
                                                                                                value);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPROGRAMUNIFORM2UIV,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32     (program),
            APIInterceptor::APIFunctionArgument::create_i32     (location),
            APIInterceptor::APIFunctionArgument::create_i32     (count),
            APIInterceptor::APIFunctionArgument::create_u32_ptr (value),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPROGRAMUNIFORM2UIV,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}

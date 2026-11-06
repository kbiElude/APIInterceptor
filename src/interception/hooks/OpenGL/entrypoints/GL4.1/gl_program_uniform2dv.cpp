/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/callbacks.h"
#include "common/logger.h"
#include "common/macros.h"
#include "common/memory_chunk.h"
#include "common/tracker.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform2dv.h"
#include "interception/hooks/OpenGL/globals.h"
#include "interception/hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiProgramUniform2dv(GLuint          program,
                                                                  GLint           location,
                                                                  GLsizei         count,
                                                                  const GLdouble* value)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    APIInterceptor::MemoryChunk             value_chunk(value,
                                                        count * 2,
                                                        sizeof(GLdouble));

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glProgramUniform2dv(program=[%u] location=[%d] count=[%d] value=[%p])",
                 program,
                 location,
                 static_cast<int32_t>(count),
                 value);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPROGRAMUNIFORM2DV,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32          (program),
                APIInterceptor::APIFunctionArgument::create_i32          (location),
                APIInterceptor::APIFunctionArgument::create_i32          (count),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(value_chunk.get_id() ),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPROGRAMUNIFORM2DV,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLPROGRAMUNIFORM2DVPROC>(Interception::Hooks::OpenGL::g_cached_gl_program_uniform2dv)(program,
                                                                                                                   location,
                                                                                                                   count,
                                                                                                                   value);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPROGRAMUNIFORM2DV,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32          (program),
            APIInterceptor::APIFunctionArgument::create_i32          (location),
            APIInterceptor::APIFunctionArgument::create_i32          (count),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(value_chunk.get_id() ),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPROGRAMUNIFORM2DV,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}

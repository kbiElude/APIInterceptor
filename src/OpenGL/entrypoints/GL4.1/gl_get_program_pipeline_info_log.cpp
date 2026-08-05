/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.1/gl_get_program_pipeline_info_log.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetProgramPipelineInfoLog(GLuint    pipeline,
                                                     GLsizei   bufSize,
                                                     GLsizei*  length,
                                                     GLchar*   infoLog)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetProgramPipelineInfoLog(pipeline=[%u] bufSize=[%d] length=[%p] infoLog=[%p])",
                 pipeline,
                 static_cast<int32_t>(bufSize),
                 length,
                 infoLog);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETPROGRAMPIPELINEINFOLOG,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32     (pipeline),
                APIInterceptor::APIFunctionArgument::create_i32     (bufSize),
                APIInterceptor::APIFunctionArgument::create_i32_ptr (length),
                APIInterceptor::APIFunctionArgument::create_i8_ptr  (infoLog),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETPROGRAMPIPELINEINFOLOG,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETPROGRAMPIPELINEINFOLOGPROC>(OpenGL::g_cached_gl_get_program_pipeline_info_log)(pipeline,
                                                                                                                bufSize,
                                                                                                                length,
                                                                                                                infoLog);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETPROGRAMPIPELINEINFOLOG,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;
        const auto                          length_chunk_id  = APIInterceptor::register_data_chunk(length,
                                                                                                   (length != nullptr) ? sizeof(GLsizei) : 0);
        const auto                          info_log_chunk_id = APIInterceptor::register_data_chunk(infoLog,
                                                                                                    (infoLog != nullptr) ? static_cast<uint32_t>(bufSize) : 0);

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32           (pipeline),
            APIInterceptor::APIFunctionArgument::create_i32           (bufSize),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id (length_chunk_id),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id (info_log_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETPROGRAMPIPELINEINFOLOG,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}

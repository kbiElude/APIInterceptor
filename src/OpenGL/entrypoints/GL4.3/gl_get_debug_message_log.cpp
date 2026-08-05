/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_get_debug_message_log.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

GLuint AI_APIENTRY OpenGL::aiGetDebugMessageLog(GLuint    count,
                                                GLsizei   bufSize,
                                                GLenum*   sources,
                                                GLenum*   types,
                                                GLuint*   ids,
                                                GLenum*   severities,
                                                GLsizei*  lengths,
                                                GLchar*   messageLog)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    GLuint                                  result                 = 0;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetDebugMessageLog(count=[%u] bufSize=[%d] sources=[%p] types=[%p] ids=[%p] severities=[%p] lengths=[%p] messageLog=[%p])",
                 count,
                 static_cast<int32_t>(bufSize),
                 sources,
                 types,
                 ids,
                 severities,
                 lengths,
                 messageLog);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETDEBUGMESSAGELOG,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32    (count),
                APIInterceptor::APIFunctionArgument::create_i32    (bufSize),
                APIInterceptor::APIFunctionArgument::create_u32_ptr(sources),
                APIInterceptor::APIFunctionArgument::create_u32_ptr(types),
                APIInterceptor::APIFunctionArgument::create_u32_ptr(ids),
                APIInterceptor::APIFunctionArgument::create_u32_ptr(severities),
                APIInterceptor::APIFunctionArgument::create_i32_ptr(lengths),
                APIInterceptor::APIFunctionArgument::create_i8_ptr (messageLog),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETDEBUGMESSAGELOG,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNGLGETDEBUGMESSAGELOGPROC>(OpenGL::g_cached_gl_get_debug_message_log)(count,
                                                                                                           bufSize,
                                                                                                           sources,
                                                                                                           types,
                                                                                                           ids,
                                                                                                           severities,
                                                                                                           lengths,
                                                                                                           messageLog);
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETDEBUGMESSAGELOG,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const auto result_arg           = APIInterceptor::APIFunctionArgument::create_u32(result);
            const auto sources_chunk_id     = APIInterceptor::register_data_chunk(sources,
                                                                                  (sources != nullptr) ? count * sizeof(GLenum) : 0);
            const auto types_chunk_id       = APIInterceptor::register_data_chunk(types,
                                                                                  (types != nullptr) ? count * sizeof(GLenum) : 0);
            const auto ids_chunk_id         = APIInterceptor::register_data_chunk(ids,
                                                                                  (ids != nullptr) ? count * sizeof(GLuint) : 0);
            const auto severities_chunk_id  = APIInterceptor::register_data_chunk(severities,
                                                                                  (severities != nullptr) ? count * sizeof(GLenum) : 0);
            const auto lengths_chunk_id     = APIInterceptor::register_data_chunk(lengths,
                                                                                  (lengths != nullptr) ? count * sizeof(GLsizei) : 0);
            const auto message_log_chunk_id = APIInterceptor::register_data_chunk(messageLog,
                                                                                  (messageLog != nullptr) ? static_cast<uint32_t>(bufSize) : 0);

            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32           (count),
                APIInterceptor::APIFunctionArgument::create_i32           (bufSize),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id (sources_chunk_id),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id (types_chunk_id),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id (ids_chunk_id),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id (severities_chunk_id),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id (lengths_chunk_id),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id (message_log_chunk_id),
            };

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETDEBUGMESSAGELOG,
                                   post_callback_func_arg,
                                   static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                                   args,
                                  &result_arg);
        }
    }

    return result;
}

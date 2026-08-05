/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.1/gl_get_program_binary.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetProgramBinary(GLuint    program,
                                            GLsizei   bufSize,
                                            GLsizei*  length,
                                            GLenum*   binaryFormat,
                                            void*     binary)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetProgramBinary(program=[%u] bufSize=[%d] length=[%p] binaryFormat=[%p] binary=[%p])",
                 program,
                 static_cast<int32_t>(bufSize),
                 length,
                 binaryFormat,
                 binary);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETPROGRAMBINARY,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32      (program),
                APIInterceptor::APIFunctionArgument::create_i32      (bufSize),
                APIInterceptor::APIFunctionArgument::create_i32_ptr  (length),
                APIInterceptor::APIFunctionArgument::create_u32_ptr  (binaryFormat),
                APIInterceptor::APIFunctionArgument::create_void_ptr (binary),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETPROGRAMBINARY,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETPROGRAMBINARYPROC>(OpenGL::g_cached_gl_get_program_binary)(program,
                                                                                             bufSize,
                                                                                             length,
                                                                                             binaryFormat,
                                                                                             binary);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETPROGRAMBINARY,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;
        const auto                          length_chunk_id       = APIInterceptor::register_data_chunk(length,
                                                                                                        (length != nullptr) ? sizeof(GLsizei) : 0);
        const auto                          binary_format_chunk_id = APIInterceptor::register_data_chunk(binaryFormat,
                                                                                                         (binaryFormat != nullptr) ? sizeof(GLuint) : 0);
        const auto                          binary_chunk_id       = APIInterceptor::register_data_chunk(binary,
                                                                                                        (binary != nullptr) ? static_cast<uint32_t>(bufSize) : 0);

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32           (program),
            APIInterceptor::APIFunctionArgument::create_i32           (bufSize),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id (length_chunk_id),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id (binary_format_chunk_id),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id (binary_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETPROGRAMBINARY,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}

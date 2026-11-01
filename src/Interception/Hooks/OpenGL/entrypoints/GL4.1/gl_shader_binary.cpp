/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/memory_chunk.h"
#include "Common/tracker.h"
#include "Interception/Hooks/OpenGL/entrypoints/GL4.1/gl_shader_binary.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Core/OpenGLUtils/utils_enum.h"
#include "Interception/Hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiShaderBinary(GLsizei       count,
                                                             const GLuint* shaders,
                                                             GLenum        binaryformat,
                                                             const void*   binary,
                                                             GLsizei       length)
{
    APIInterceptor::MemoryChunk             binary_chunk(binary,
                                                         length,
                                                         sizeof(uint8_t));
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    APIInterceptor::MemoryChunk             shaders_chunk(shaders,
                                                          count,
                                                          sizeof(GLuint));
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glShaderBinary(count=[%d] shaders=[%p] binaryformat=[%s] binary=[%p] length=[%d])",
                 static_cast<int32_t>(count),
                 shaders,
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(binaryformat),
                 binary,
                 static_cast<int32_t>(length) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLSHADERBINARY,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32          (count),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(shaders_chunk.get_id() ),
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (binaryformat),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(binary_chunk.get_id() ),
                APIInterceptor::APIFunctionArgument::create_i32          (length),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLSHADERBINARY,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLSHADERBINARYPROC>(Interception::Hooks::OpenGL::g_cached_gl_shader_binary)(count,
                                                                                                         shaders,
                                                                                                         binaryformat,
                                                                                                         binary,
                                                                                                         length);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLSHADERBINARY,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32          (count),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(shaders_chunk.get_id() ),
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (binaryformat),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(binary_chunk.get_id() ),
            APIInterceptor::APIFunctionArgument::create_i32          (length),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLSHADERBINARY,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}

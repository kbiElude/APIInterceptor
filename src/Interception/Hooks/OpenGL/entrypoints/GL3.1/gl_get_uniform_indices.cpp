/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "Interception/Hooks/OpenGL/entrypoints/GL3.1/gl_get_uniform_indices.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Hooks/OpenGL/string_array_chunk.h"
#include "Interception/Hooks/WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetUniformIndices(GLuint               program,
                                             GLsizei              uniformCount,
                                             const GLchar* const* uniformNames,
                                             GLuint*              uniformIndices)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    OpenGL::StringArrayChunk                uniform_names_chunk(uniformNames,
                                                                uniformCount,
                                                                nullptr);

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetUniformIndices(program=[%u] uniformCount=[%d] uniformNames=[%p] uniformIndices=[%p])",
                 program,
                 static_cast<int32_t>(uniformCount),
                 uniformNames,
                 uniformIndices);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETUNIFORMINDICES,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32          (program),
                APIInterceptor::APIFunctionArgument::create_i32          (uniformCount),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(uniform_names_chunk.get_id() ),
                APIInterceptor::APIFunctionArgument::create_void_ptr     (uniformIndices),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETUNIFORMINDICES,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETUNIFORMINDICESPROC>(OpenGL::g_cached_gl_get_uniform_indices)(program,
                                                                                              uniformCount,
                                                                                              uniformNames,
                                                                                              uniformIndices);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETUNIFORMINDICES,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const auto uniform_indices_chunk_id = APIInterceptor::register_data_chunk(uniformIndices,
                                                                                  (uniformIndices != nullptr && uniformCount > 0) ? sizeof(GLuint) * static_cast<uint32_t>(uniformCount)
                                                                                                                                  : 0);

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32          (program),
            APIInterceptor::APIFunctionArgument::create_i32          (uniformCount),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(uniform_names_chunk.get_id() ),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(uniform_indices_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETUNIFORMINDICES,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}

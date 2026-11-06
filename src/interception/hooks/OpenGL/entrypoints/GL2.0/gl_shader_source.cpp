/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/callbacks.h"
#include "common/logger.h"
#include "common/macros.h"
#include "common/tracker.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_shader_source.h"
#include "interception/hooks/OpenGL/globals.h"
#include "interception/hooks/OpenGL/string_array_chunk.h"
#include "interception/hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiShaderSource(GLuint               shader,
                                                             GLsizei              count,
                                                             const GLchar* const* string,
                                                             const GLint*         length)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    Interception::Hooks::OpenGL::StringArrayChunk                strings_chunk(string,
                                                                               count,
                                                                               length);
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glShaderSource(shader=[%u] count=[%d] string=[%p] length=[%p])",
                 shader,
                 static_cast<int32_t>(count),
                 string,
                 length);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLSHADERSOURCE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32          (shader),
                APIInterceptor::APIFunctionArgument::create_i32          (count),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(strings_chunk.get_id() ),
                APIInterceptor::APIFunctionArgument::create_void_ptr     (length),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLSHADERSOURCE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLSHADERSOURCEPROC>(Interception::Hooks::OpenGL::g_cached_gl_shader_source)(shader,
                                                                                                        count,
                                                                                                        string,
                                                                                                        length);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLSHADERSOURCE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32          (shader),
            APIInterceptor::APIFunctionArgument::create_i32          (count),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(strings_chunk.get_id() ),
            APIInterceptor::APIFunctionArgument::create_void_ptr     (length),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLSHADERSOURCE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}

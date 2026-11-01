/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "Interception/Hooks/OpenGL/entrypoints/GL3.3/gl_get_frag_data_index.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Hooks/OpenGL/string_chunk.h"
#include "Interception/Hooks/WGL/globals.h"

GLint AI_APIENTRY Interception::Hooks::OpenGL::aiGetFragDataIndex(GLuint        program,
                                                                  const GLchar* name)
{
    Interception::Hooks::OpenGL::StringChunk                     name_chunk(name);
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    GLint                                   result                 = -1;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetFragDataIndex(program=[%u] name=[%s])",
                 program,
                 name);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETFRAGDATAINDEX,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32          (program),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(name_chunk.get_id() ),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETFRAGDATAINDEX,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNGLGETFRAGDATAINDEXPROC>(Interception::Hooks::OpenGL::g_cached_gl_get_frag_data_index)(program,
                                                                                                                            name);
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETFRAGDATAINDEX,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const auto result_arg = APIInterceptor::APIFunctionArgument::create_i32(result);

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETFRAGDATAINDEX,
                                   post_callback_func_arg,
                                   0,       /* in_n_arguments_out   */
                                   nullptr, /* in_arguments_out_ptr */
                                  &result_arg);
        }
    }

    return result;
}

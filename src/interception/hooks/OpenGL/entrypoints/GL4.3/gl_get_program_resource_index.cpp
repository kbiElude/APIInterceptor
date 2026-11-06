/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/callbacks.h"
#include "common/logger.h"
#include "common/macros.h"
#include "common/tracker.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_get_program_resource_index.h"
#include "interception/hooks/OpenGL/globals.h"
#include "interception/hooks/OpenGL/string_chunk.h"
#include "interception/core/OpenGLUtils/utils_enum.h"
#include "interception/hooks/WGL/globals.h"

GLuint AI_APIENTRY Interception::Hooks::OpenGL::aiGetProgramResourceIndex(GLuint        program,
                                                                          GLenum        programInterface,
                                                                          const GLchar* name)
{
    Interception::Hooks::OpenGL::StringChunk                     name_chunk(name);
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    GLuint                                  result                 = 0xFFFFFFFFu;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetProgramResourceIndex(program=[%u] programInterface=[%s] name=[%s])",
                 program,
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(programInterface),
                 name);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETPROGRAMRESOURCEINDEX,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32          (program),
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (programInterface),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(name_chunk.get_id() ),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETPROGRAMRESOURCEINDEX,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNGLGETPROGRAMRESOURCEINDEXPROC>(Interception::Hooks::OpenGL::g_cached_gl_get_program_resource_index)(program,
                                                                                                                                          programInterface,
                                                                                                                                          name);
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETPROGRAMRESOURCEINDEX,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const auto result_arg = APIInterceptor::APIFunctionArgument::create_u32(result);

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETPROGRAMRESOURCEINDEX,
                                   post_callback_func_arg,
                                   0,
                                   nullptr,
                                  &result_arg);
        }
    }

    return result;
}

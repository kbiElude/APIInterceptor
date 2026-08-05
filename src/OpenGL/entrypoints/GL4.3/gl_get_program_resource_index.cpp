/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_get_program_resource_index.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

GLuint AI_APIENTRY OpenGL::aiGetProgramResourceIndex(GLuint        program,
                                                     GLenum        programInterface,
                                                     const GLchar* name)
{
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
                 OpenGL::Utils::get_raw_string_for_gl_enum(programInterface),
                 name);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETPROGRAMRESOURCEINDEX,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32       (program),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(programInterface),
                APIInterceptor::APIFunctionArgument::create_i8_ptr    (name),
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
        result = reinterpret_cast<PFNGLGETPROGRAMRESOURCEINDEXPROC>(OpenGL::g_cached_gl_get_program_resource_index)(program,
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

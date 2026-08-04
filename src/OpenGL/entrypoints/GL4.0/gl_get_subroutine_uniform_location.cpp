/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.0/gl_get_subroutine_uniform_location.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

GLint AI_APIENTRY OpenGL::aiGetSubroutineUniformLocation(GLuint        program,
                                                         GLenum        shadertype,
                                                         const GLchar* name)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    GLint                                   result                 = -1;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetSubroutineUniformLocation(program=[%u] shadertype=[%s] name=[%s])",
                 program,
                 OpenGL::Utils::get_raw_string_for_gl_enum(shadertype),
                 name);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETSUBROUTINEUNIFORMLOCATION,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32       (program),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(shadertype),
                APIInterceptor::APIFunctionArgument::create_i8_ptr    (name),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETSUBROUTINEUNIFORMLOCATION,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC>(OpenGL::g_cached_gl_get_subroutine_uniform_location)(program,
                                                                                                                              shadertype,
                                                                                                                              name);
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETSUBROUTINEUNIFORMLOCATION,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const auto result_arg = APIInterceptor::APIFunctionArgument::create_i32(result);

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETSUBROUTINEUNIFORMLOCATION,
                                   post_callback_func_arg,
                                   0,
                                   nullptr,
                                  &result_arg);
        }
    }

    return result;
}

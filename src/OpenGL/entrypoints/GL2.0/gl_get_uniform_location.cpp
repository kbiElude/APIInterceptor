/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_uniform_location.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLint AI_APIENTRY OpenGL::aiGetUniformLocation(GLuint        program,
                                               const GLchar* name)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    GLint                                   result                 = -1;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetUniformLocation(program=[%u] name=[%s])",
                 program,
                 name);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETUNIFORMLOCATION,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32     (program),
                APIInterceptor::APIFunctionArgument::create_void_ptr(name),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETUNIFORMLOCATION,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNGLGETUNIFORMLOCATIONPROC>(OpenGL::g_cached_gl_get_uniform_location)(program,
                                                                                                         name);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETUNIFORMLOCATION,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg = APIInterceptor::APIFunctionArgument::create_i32(result);

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32     (program),
            APIInterceptor::APIFunctionArgument::create_void_ptr(name),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETUNIFORMLOCATION,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }

    return result;
}

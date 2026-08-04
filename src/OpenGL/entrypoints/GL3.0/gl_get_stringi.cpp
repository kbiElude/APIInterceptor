/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_stringi.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

const GLubyte* APIENTRY OpenGL::aiGetStringi(GLenum name,
                                             GLuint index)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    const GLubyte*                          result_ptr             = reinterpret_cast<const GLubyte*>("?!");
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetStringi(name=[%s] index=[%u])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(name),
                 index);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETSTRINGI,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(name),
                APIInterceptor::APIFunctionArgument::create_u32       (index),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETSTRINGI,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        result_ptr = reinterpret_cast<PFNGLGETSTRINGIPROC>(OpenGL::g_cached_gl_get_stringi)(name,
                                                                                            index);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETSTRINGI,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(name),
            APIInterceptor::APIFunctionArgument::create_u32       (index),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETSTRINGI,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }

    return result_ptr;
}

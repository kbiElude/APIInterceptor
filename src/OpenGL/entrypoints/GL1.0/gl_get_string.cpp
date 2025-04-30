/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_string.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

const GLubyte* APIENTRY OpenGL::aiGetString(GLenum name)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    const GLubyte*                      result_ptr          = reinterpret_cast<const GLubyte*>("?!");
    bool                                should_pass_through = true;

    AI_TRACE("glGetString(name=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(name) );

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETSTRING,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(name),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETSTRING,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        result_ptr = reinterpret_cast<PFNGLGETSTRINGPROC>(OpenGL::g_cached_gl_get_string)(name);
    }

    return result_ptr;
}
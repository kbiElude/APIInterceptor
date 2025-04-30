/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_is_enabled.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsEnabled(GLenum cap)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    GLboolean                           result              = GL_FALSE;
    bool                                should_pass_through = true;

    AI_TRACE("glIsEnabled(cap=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(cap) );

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLISENABLED,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(cap),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLISENABLED,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNGLISENABLEDPROC>(OpenGL::g_cached_gl_is_enabled)(cap);
    }

    return result;
}
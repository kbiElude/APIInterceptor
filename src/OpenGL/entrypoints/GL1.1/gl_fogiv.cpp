/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_fogiv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFogiv(GLenum       pname,
                                 const GLint* params)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glFogiv(pname=[%s], params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLFOGIV,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32    (pname),
            APIInterceptor::APIFunctionArgument::create_i32_ptr(params),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLFOGIV,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    reinterpret_cast<PFNGLFOGIVPROC>(OpenGL::g_cached_gl_fogiv)(pname,
                                                                params);
}
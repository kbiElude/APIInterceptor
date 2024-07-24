/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_fogf.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFogf(GLenum  pname,
                                GLfloat param)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glFogf(pname=[%s], param=[%.4f])",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             param);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLFOGF,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32 (pname),
            APIInterceptor::APIFunctionArgument::create_fp32(param),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLFOGF,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    reinterpret_cast<PFNGLFOGFPROC>(OpenGL::g_cached_gl_fogf)(pname,
                                                              param);
}
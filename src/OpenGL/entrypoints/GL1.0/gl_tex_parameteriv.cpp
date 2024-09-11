/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_tex_parameteriv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexParameteriv(GLenum       target,
                                          GLenum       pname,
                                          const GLint* params)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glTexParameteriv(target=[%s] pname=[%s] params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXPARAMETERIV,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32    (target),
            APIInterceptor::APIFunctionArgument::create_u32    (pname),
            APIInterceptor::APIFunctionArgument::create_i32_ptr(params),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXPARAMETERIV,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (OpenGL::g_cached_gl_tex_parameteriv == nullptr)
    {
        OpenGL::g_cached_gl_tex_parameteriv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glTexParameteriv");
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXPARAMETERIVPROC>(OpenGL::g_cached_gl_tex_parameteriv)(target,
                                                                                       pname,
                                                                                       params);
    }
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_get_tex_parameteriv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetTexParameteriv(GLenum target,
                                             GLenum pname,
                                             GLint* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetTexParameteriv(target=[%s] pname=[%s] params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_get_tex_parameteriv == nullptr)
    {
        OpenGL::g_cached_gl_get_tex_parameteriv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetTexParameteriv");
    }

    reinterpret_cast<PFNGLGETTEXPARAMETERIVPROC>(OpenGL::g_cached_gl_get_tex_parameteriv)(target,
                                                                                          pname,
                                                                                          params);
}
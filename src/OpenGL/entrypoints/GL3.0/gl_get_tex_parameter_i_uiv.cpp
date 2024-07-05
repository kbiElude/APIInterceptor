/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_get_tex_parameter_i_uiv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetTexParameterIuiv(GLenum  target,
                                               GLenum  pname,
                                               GLuint* params)
{
    AI_TRACE("glGetTexParameterIuiv(target=[%s] pname=[%s] params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_get_tex_parameter_i_uiv == nullptr)
    {
        OpenGL::g_cached_gl_get_tex_parameter_i_uiv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetTexParameterIuiv");
    }

    reinterpret_cast<PFNGLGETTEXPARAMETERIUIVPROC>(OpenGL::g_cached_gl_get_tex_parameter_i_uiv)(target,
                                                                                                pname,
                                                                                                params);
}
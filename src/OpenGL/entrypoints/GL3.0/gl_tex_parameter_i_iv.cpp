/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_tex_parameter_i_iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexParameterIiv(GLenum       target,
                                           GLenum       pname,
                                           const GLint* params)
{
    AI_TRACE("glTexParameterIiv(target=[%s] pname=[%s] params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_tex_parameter_i_iv == nullptr)
    {
        OpenGL::g_cached_gl_tex_parameter_i_iv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glTexParameterIiv");
    }

    reinterpret_cast<PFNGLTEXPARAMETERIIVPROC>(OpenGL::g_cached_gl_tex_parameter_i_iv)(target,
                                                                                       pname,
                                                                                       params);
}
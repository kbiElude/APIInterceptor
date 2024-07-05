/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_tex_parameteriv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexParameteriv(GLenum       target,
                                          GLenum       pname,
                                          const GLint* params)
{
    const auto dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    AI_TRACE("glTexParameteriv(target=[%s] pname=[%s] params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_tex_parameteriv == nullptr)
    {
        OpenGL::g_cached_gl_tex_parameteriv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glTexParameteriv");
    }

    reinterpret_cast<PFNGLTEXPARAMETERIVPROC>(OpenGL::g_cached_gl_tex_parameteriv)(target,
                                                                                   pname,
                                                                                   params);
}
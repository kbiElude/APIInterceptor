/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_tex_parameteri.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexParameteri(GLenum target,
                                         GLenum pname,
                                         GLint  param)
{
    const auto dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    AI_TRACE("glTexParameteri(target=[%s] pname=[%s] param=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             param);

    if (OpenGL::g_cached_gl_tex_parameteri == nullptr)
    {
        OpenGL::g_cached_gl_tex_parameteri = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glTexParameteri");
    }

    reinterpret_cast<PFNGLTEXPARAMETERIPROC>(OpenGL::g_cached_gl_tex_parameteri)(target,
                                                                                 pname,
                                                                                 param);
}
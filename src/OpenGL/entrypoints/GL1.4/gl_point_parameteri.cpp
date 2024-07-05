/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.4/gl_point_parameteri.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPointParameteri(GLenum pname,
                                           GLint  param)
{
    AI_TRACE("glPointParameteri(pname=[%s] param=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             param);

    if (OpenGL::g_cached_gl_point_parameteri == nullptr)
    {
        OpenGL::g_cached_gl_point_parameteri = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glPointParameteri");
    }

    reinterpret_cast<PFNGLPOINTPARAMETERIPROC>(g_cached_gl_point_parameteri)(pname,
                                                                             param);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.4/gl_point_parameterf.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPointParameterf(GLenum  pname,
                                           GLfloat param)
{
    AI_TRACE("glPointParameterf(pname=[%s] param=[%.4f])",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             param);

    if (OpenGL::g_cached_gl_point_parameterf == nullptr)
    {
        OpenGL::g_cached_gl_point_parameterf = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glPointParameterf");
    }

    reinterpret_cast<PFNGLPOINTPARAMETERFPROC>(OpenGL::g_cached_gl_point_parameterf)(pname,
                                                                                     param);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_polygon_mode.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPolygonMode(GLenum face,
                                       GLenum mode)
{
    AI_TRACE("glPolygonMode(face=[%s] mode=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(face),
             OpenGL::Utils::get_raw_string_for_gl_enum(mode) );


    if (OpenGL::g_cached_gl_polygon_mode == nullptr)
    {
        OpenGL::g_cached_gl_polygon_mode = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glPolygonMode");
    }

    reinterpret_cast<PFNGLPOLYGONMODEPROC>(g_cached_gl_polygon_mode)(face,
                                                                     mode);
}
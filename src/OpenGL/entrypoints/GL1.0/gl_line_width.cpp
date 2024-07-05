/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_line_width.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiLineWidth(GLfloat width)
{
    const auto dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    AI_TRACE("glLineWidth(width=[%.4f])",
             width);

    if (OpenGL::g_cached_gl_line_width == nullptr)
    {
        OpenGL::g_cached_gl_line_width = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glLineWidth");
    }

    reinterpret_cast<PFNGLLINEWIDTHPROC>(OpenGL::g_cached_gl_line_width)(width);
}
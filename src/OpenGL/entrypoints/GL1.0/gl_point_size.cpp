/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_point_size.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPointSize(GLfloat size)
{
    const auto dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    AI_TRACE("glPointSize(size=[%.4f])",
             size);

    if (OpenGL::g_cached_gl_point_size == nullptr)
    {
        OpenGL::g_cached_gl_point_size = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glPointSize");
    }

    reinterpret_cast<PFNGLPOINTSIZEPROC>(g_cached_gl_point_size)(size);
}
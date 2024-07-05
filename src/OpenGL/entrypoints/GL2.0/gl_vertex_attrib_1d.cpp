/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1d.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib1d(GLuint   index,
                                          GLdouble x)
{
    const auto& dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    AI_TRACE("glVertexAttrib1d(index=[%u] x=[%.4f])",
             index,
             static_cast<float>(x) );

    if (OpenGL::g_cached_gl_vertex_attrib_1d == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_1d = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttrib1d");
    }

    reinterpret_cast<PFNGLVERTEXATTRIB1DPROC>(OpenGL::g_cached_gl_vertex_attrib_1d)(index,
                                                                                    x);
}
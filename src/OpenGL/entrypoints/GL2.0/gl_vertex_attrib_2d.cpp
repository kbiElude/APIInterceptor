/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2d.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib2d(GLuint   index,
                                          GLdouble x,
                                          GLdouble y)
{
    AI_TRACE("glVertexAttrib2d(index=[%u] x=[%.4f] y=[%.4f])",
             index,
             static_cast<float>(x),
             static_cast<float>(y) );

    if (OpenGL::g_cached_gl_vertex_attrib_2d == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_2d = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttrib2d");
    }

    reinterpret_cast<PFNGLVERTEXATTRIB2DPROC>(OpenGL::g_cached_gl_vertex_attrib_2d)(index,
                                                                                    x,
                                                                                    y);
}
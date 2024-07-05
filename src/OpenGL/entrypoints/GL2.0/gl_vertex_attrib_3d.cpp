/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3d.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib3d(GLuint   index,
                                          GLdouble x,
                                          GLdouble y,
                                          GLdouble z)
{
    AI_TRACE("glVertexAttrib3d(index=[%u] x=[%.4f] y=[%.4f] z=[%.4f])",
             index,
             static_cast<float>(x),
             static_cast<float>(y),
             static_cast<float>(z) );

    if (OpenGL::g_cached_gl_vertex_attrib_3d == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_3d = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttrib3d");
    }

    reinterpret_cast<PFNGLVERTEXATTRIB3DPROC>(OpenGL::g_cached_gl_vertex_attrib_3d)(index,
                                                                                    x,
                                                                                    y,
                                                                                    z);
}
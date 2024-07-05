/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2f.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib2f(GLuint  index,
                                          GLfloat x,
                                          GLfloat y)
{
    AI_TRACE("glVertexAttrib2f(index=[%u] x=[%.4f] y=[%.4f])",
             index,
             x,
             y);

    if (OpenGL::g_cached_gl_vertex_attrib_2f == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_2f = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttrib2f");
    }

    reinterpret_cast<PFNGLVERTEXATTRIB2FPROC>(OpenGL::g_cached_gl_vertex_attrib_2f)(index,
                                                                                    x,
                                                                                    y);
}
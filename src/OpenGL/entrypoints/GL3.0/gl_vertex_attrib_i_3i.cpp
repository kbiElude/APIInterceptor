/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3i.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI3i(GLuint index,
                                           GLint  x,
                                           GLint  y,
                                           GLint  z)
{
    AI_TRACE("glVertexAttribI3i(index=[%u] x=[%d] y=[%d] z=[%d])",
             index,
             x,
             y,
             z);

    if (OpenGL::g_cached_gl_vertex_attrib_i_3i == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_i_3i = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttribI3i");
    }

    reinterpret_cast<PFNGLVERTEXATTRIBI3IPROC>(OpenGL::g_cached_gl_vertex_attrib_i_3i)(index,
                                                                                       x,
                                                                                       y,
                                                                                       z);
}

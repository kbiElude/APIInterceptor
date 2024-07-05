/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_1i.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI1i(GLuint index,
                                           GLint  x)
{
    AI_TRACE("glVertexAttribI1i(index=[%u] x=[%d])",
             index,
             x);

    if (OpenGL::g_cached_gl_vertex_attrib_i_1i == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_i_1i = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttribI1i");
    }

    reinterpret_cast<PFNGLVERTEXATTRIBI1IPROC>(OpenGL::g_cached_gl_vertex_attrib_i_1i)(index,
                                                                                       x);
}
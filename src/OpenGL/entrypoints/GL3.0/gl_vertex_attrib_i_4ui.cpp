/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4ui.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI4ui(GLuint index,
                                            GLuint x,
                                            GLuint y,
                                            GLuint z,
                                            GLuint w)
{
    AI_TRACE("glVertexAttribI4ui(index=[%u] x=[%u] y=[%u] z=[%u] w=[%u])",
             index,
             x,
             y,
             z,
             w);

    if (OpenGL::g_cached_gl_vertex_attrib_i_4ui == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_i_4ui = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttribI4ui");
    }

    reinterpret_cast<PFNGLVERTEXATTRIBI4UIPROC>(OpenGL::g_cached_gl_vertex_attrib_i_4ui)(index,
                                                                                         x,
                                                                                         y,
                                                                                         z,
                                                                                         w);
}
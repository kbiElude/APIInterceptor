/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3ui.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI3ui(GLuint index,
                                            GLuint x,
                                            GLuint y,
                                            GLuint z)
{
    AI_TRACE("glVertexAttribI3ui(index=[%u] x=[%u] y=[%u] z=[%u])",
             index,
             x,
             y,
             z);

    if (OpenGL::g_cached_gl_vertex_attrib_i_3ui == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_i_3ui = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttribI3ui");
    }

    reinterpret_cast<PFNGLVERTEXATTRIBI3UIPROC>(OpenGL::g_cached_gl_vertex_attrib_i_3ui)(index,
                                                                                         x,
                                                                                         y,
                                                                                         z);
}
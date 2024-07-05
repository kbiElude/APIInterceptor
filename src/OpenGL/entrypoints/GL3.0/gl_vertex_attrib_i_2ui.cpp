/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_2ui.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI2ui(GLuint index,
                                            GLuint x,
                                            GLuint y)
{
    AI_TRACE("glVertexAttribI2ui(index=[%u] x=[%u] y=[%u])",
             index,
             x,
             y);

    if (OpenGL::g_cached_gl_vertex_attrib_i_2ui == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_i_2ui = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttribI2ui");
    }

    reinterpret_cast<PFNGLVERTEXATTRIBI2UIPROC>(OpenGL::g_cached_gl_vertex_attrib_i_2ui)(index,
                                                                                         x,
                                                                                         y);
}
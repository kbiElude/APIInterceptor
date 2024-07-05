/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_1ui.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI1ui(GLuint index,
                                            GLuint x)
{
    AI_TRACE("glVertexAttribI1ui(index=[%u] x=[%u])",
             index,
             x);

    if (OpenGL::g_cached_gl_vertex_attrib_i_1ui == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_i_1ui = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttribI1ui");
    }

    reinterpret_cast<PFNGLVERTEXATTRIBI1UIPROC>(OpenGL::g_cached_gl_vertex_attrib_i_1ui)(index,
                                                                                         x);
}
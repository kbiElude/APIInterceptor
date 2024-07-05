/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4iv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI4iv(GLuint       index,
                                            const GLint* v)
{
    /* TODO: Make me more useful */
    AI_TRACE("glVertexAttribI4iv(index=[%u] v=[%p])",
             index,
             v);

    if (OpenGL::g_cached_gl_vertex_attrib_i_4iv == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_i_4iv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttribI4iv");
    }

    reinterpret_cast<PFNGLVERTEXATTRIBI4IVPROC>(OpenGL::g_cached_gl_vertex_attrib_i_4iv)(index,
                                                                                         v);
}

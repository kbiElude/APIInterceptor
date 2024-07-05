/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4sv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI4sv(GLuint         index,
                                            const GLshort* v)
{
    /* TODO: Make me more useful */
    AI_TRACE("glVertexAttribI4sv(index=[%u] v=[%p])",
             index,
             v);

    if (OpenGL::g_cached_gl_vertex_attrib_i_4sv == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_i_4sv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttribI4sv");
    }

    reinterpret_cast<PFNGLVERTEXATTRIBI4SVPROC>(OpenGL::g_cached_gl_vertex_attrib_i_4sv)(index,
                                                                                         v);
}
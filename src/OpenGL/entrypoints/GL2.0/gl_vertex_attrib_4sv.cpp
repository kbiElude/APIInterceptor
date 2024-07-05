/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4sv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib4sv(GLuint         index,
                                           const GLshort* v)
{
    /* TODO: Make me more useful */
    AI_TRACE("glVertexAttrib4sv(index=[%u] v=[%p])",
             index,
             v);

    if (OpenGL::g_cached_gl_vertex_attrib_4sv == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_4sv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttrib4sv");
    }

    reinterpret_cast<PFNGLVERTEXATTRIB4SVPROC>(OpenGL::g_cached_gl_vertex_attrib_4sv)(index,
                                                                                      v);
}
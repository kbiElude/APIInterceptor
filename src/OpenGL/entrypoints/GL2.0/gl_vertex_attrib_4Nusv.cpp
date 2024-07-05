/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nusv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib4Nusv(GLuint          index,
                                             const GLushort* v)
{
    /* TODO: Make me more useful */
    AI_TRACE("glVertexAttrib4Nusv(index=[%u] v=[%p])",
             index,
             v);

    if (OpenGL::g_cached_gl_vertex_attrib_4Nusv == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_4Nusv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttrib4Nusv");
    }

    reinterpret_cast<PFNGLVERTEXATTRIB4NUSVPROC>(OpenGL::g_cached_gl_vertex_attrib_4Nusv)(index,
                                                                                          v);
}
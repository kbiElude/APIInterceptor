/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nubv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib4Nubv(GLuint         index,
                                             const GLubyte* v)
{
    /* TODO: Make me more useful */
    AI_TRACE("glVertexAttrib4Nubv(index=[%u] v=[%p])",
             index,
             v);

    if (OpenGL::g_cached_gl_vertex_attrib_4Nubv == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_4Nubv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttrib4Nubv");
    }

    reinterpret_cast<PFNGLVERTEXATTRIB4NUBVPROC>(OpenGL::g_cached_gl_vertex_attrib_4Nubv)(index,
                                                                                          v);
}
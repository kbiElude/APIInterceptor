/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4uiv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib4uiv(GLuint        index,
                                            const GLuint* v)
{
    /* TODO: Make me more useful */
    AI_TRACE("glVertexAttrib4uiv(index=[%u] v=[%p])",
             index,
             v);

    if (OpenGL::g_cached_gl_vertex_attrib_4uiv == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_4uiv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttrib4uiv");
    }

    reinterpret_cast<PFNGLVERTEXATTRIB4UIVPROC>(OpenGL::g_cached_gl_vertex_attrib_4uiv)(index,
                                                                                        v);
}
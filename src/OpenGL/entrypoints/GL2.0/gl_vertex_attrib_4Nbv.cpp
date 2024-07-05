/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nbv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib4Nbv(GLuint        index,
                                            const GLbyte* v)
{
    /* TODO: Make me more useful */
    AI_TRACE("glVertexAttrib4Nbv(index=[%u] v=[%p])",
             index,
             v);

    if (OpenGL::g_cached_gl_vertex_attrib_4Nbv == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_4Nbv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttrib4Nbv");
    }

    reinterpret_cast<PFNGLVERTEXATTRIB4NBVPROC>(OpenGL::g_cached_gl_vertex_attrib_4Nbv)(index,
                                                                                        v);
}
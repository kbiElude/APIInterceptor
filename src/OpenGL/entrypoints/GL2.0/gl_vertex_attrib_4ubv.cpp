/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4ubv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib4ubv(GLuint         index,
                                            const GLubyte* v)
{
    /* TODO: Make me more useful */
    AI_TRACE("glVertexAttrib4ubv(index=[%u] v=[%p])",
             index,
             v);

    if (OpenGL::g_cached_gl_vertex_attrib_4ubv == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_4ubv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttrib4ubv");
    }

    reinterpret_cast<PFNGLVERTEXATTRIB4UBVPROC>(OpenGL::g_cached_gl_vertex_attrib_4ubv)(index,
                                                                                        v);
}
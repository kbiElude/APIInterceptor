/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nsv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib4Nsv(GLuint         index,
                                            const GLshort* v)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    /* TODO: Make me more useful */
    AI_TRACE("glVertexAttrib4Nsv(index=[%u] v=[%p])",
             index,
             v);

    if (OpenGL::g_cached_gl_vertex_attrib_4Nsv == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_4Nsv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttrib4Nsv");
    }

    reinterpret_cast<PFNGLVERTEXATTRIB4NSVPROC>(OpenGL::g_cached_gl_vertex_attrib_4Nsv)(index,
                                                                                        v);
}
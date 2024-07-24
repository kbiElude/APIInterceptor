/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4f.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib4f(GLuint  index,
                                          GLfloat x,
                                          GLfloat y,
                                          GLfloat z,
                                          GLfloat w)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glVertexAttrib4f(index=[%u] x=[%.4f] y=[%.4f] z=[%.4f] w=[%.4f])",
             index,
             x,
             y,
             z,
             w);

    if (OpenGL::g_cached_gl_vertex_attrib_4f == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_4f = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttrib4f");
    }

    reinterpret_cast<PFNGLVERTEXATTRIB4FPROC>(OpenGL::g_cached_gl_vertex_attrib_4f)(index,
                                                                                    x,
                                                                                    y,
                                                                                    z,
                                                                                    w);
}
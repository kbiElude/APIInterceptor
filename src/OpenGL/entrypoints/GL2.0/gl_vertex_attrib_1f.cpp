/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1f.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib1f(GLuint  index,
                                          GLfloat x)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glVertexAttrib1f(index=[%u] x=[%.4f])",
             index,
             x);

    reinterpret_cast<PFNGLVERTEXATTRIB1FPROC>(OpenGL::g_cached_gl_vertex_attrib_1f)(index,
                                                                                    x);
}
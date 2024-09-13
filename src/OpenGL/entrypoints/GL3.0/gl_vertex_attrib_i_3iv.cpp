/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3iv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI3iv(GLuint       index,
                                            const GLint* v)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    /* TODO: Make me more useful */
    AI_TRACE("glVertexAttribI3iv(index=[%u] v=[%p])",
             index,
             v);

    reinterpret_cast<PFNGLVERTEXATTRIBI3IVPROC>(OpenGL::g_cached_gl_vertex_attrib_i_3iv)(index,
                                                                                         v);
}
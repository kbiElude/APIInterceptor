/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3i.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI3i(GLuint index,
                                           GLint  x,
                                           GLint  y,
                                           GLint  z)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glVertexAttribI3i(index=[%u] x=[%d] y=[%d] z=[%d])",
             index,
             x,
             y,
             z);

    reinterpret_cast<PFNGLVERTEXATTRIBI3IPROC>(OpenGL::g_cached_gl_vertex_attrib_i_3i)(index,
                                                                                       x,
                                                                                       y,
                                                                                       z);
}

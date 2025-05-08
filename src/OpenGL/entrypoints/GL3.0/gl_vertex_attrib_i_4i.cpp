/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4i.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI4i(GLuint index,
                                           GLint  x,
                                           GLint  y,
                                           GLint  z,
                                           GLint  w)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glVertexAttribI4i(index=[%u] x=[%d] y=[%d] z=[%d] w=[%d])",
             index,
             x,
             y,
             z,
             w);

    reinterpret_cast<PFNGLVERTEXATTRIBI4IPROC>(OpenGL::g_cached_gl_vertex_attrib_i_4i)(index,
                                                                                       x,
                                                                                       y,
                                                                                       z,
                                                                                       w);
}
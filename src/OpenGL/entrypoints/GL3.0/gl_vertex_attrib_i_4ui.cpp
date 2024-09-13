/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4ui.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI4ui(GLuint index,
                                            GLuint x,
                                            GLuint y,
                                            GLuint z,
                                            GLuint w)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glVertexAttribI4ui(index=[%u] x=[%u] y=[%u] z=[%u] w=[%u])",
             index,
             x,
             y,
             z,
             w);

    reinterpret_cast<PFNGLVERTEXATTRIBI4UIPROC>(OpenGL::g_cached_gl_vertex_attrib_i_4ui)(index,
                                                                                         x,
                                                                                         y,
                                                                                         z,
                                                                                         w);
}
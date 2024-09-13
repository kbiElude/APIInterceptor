/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3ui.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI3ui(GLuint index,
                                            GLuint x,
                                            GLuint y,
                                            GLuint z)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glVertexAttribI3ui(index=[%u] x=[%u] y=[%u] z=[%u])",
             index,
             x,
             y,
             z);

    reinterpret_cast<PFNGLVERTEXATTRIBI3UIPROC>(OpenGL::g_cached_gl_vertex_attrib_i_3ui)(index,
                                                                                         x,
                                                                                         y,
                                                                                         z);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_2ui.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI2ui(GLuint index,
                                            GLuint x,
                                            GLuint y)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glVertexAttribI2ui(index=[%u] x=[%u] y=[%u])",
             index,
             x,
             y);

    reinterpret_cast<PFNGLVERTEXATTRIBI2UIPROC>(OpenGL::g_cached_gl_vertex_attrib_i_2ui)(index,
                                                                                         x,
                                                                                         y);
}
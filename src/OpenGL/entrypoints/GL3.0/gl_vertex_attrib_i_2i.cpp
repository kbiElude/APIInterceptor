/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_2i.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI2i(GLuint index,
                                           GLint  x,
                                           GLint  y)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glVertexAttribI2i(index=[%u] x=[%d] y=[%d])",
             index,
             x,
             y);

    reinterpret_cast<PFNGLVERTEXATTRIBI2IPROC>(OpenGL::g_cached_gl_vertex_attrib_i_2i)(index,
                                                                                       x,
                                                                                       y);
}
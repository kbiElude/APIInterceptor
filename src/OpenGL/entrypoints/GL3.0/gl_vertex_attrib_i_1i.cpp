/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_1i.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI1i(GLuint index,
                                           GLint  x)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glVertexAttribI1i(index=[%u] x=[%d])",
             index,
             x);

    reinterpret_cast<PFNGLVERTEXATTRIBI1IPROC>(OpenGL::g_cached_gl_vertex_attrib_i_1i)(index,
                                                                                       x);
}
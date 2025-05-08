/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_1ui.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI1ui(GLuint index,
                                            GLuint x)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glVertexAttribI1ui(index=[%u] x=[%u])",
             index,
             x);

    reinterpret_cast<PFNGLVERTEXATTRIBI1UIPROC>(OpenGL::g_cached_gl_vertex_attrib_i_1ui)(index,
                                                                                         x);
}
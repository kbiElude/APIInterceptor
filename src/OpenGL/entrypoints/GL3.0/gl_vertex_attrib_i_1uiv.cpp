/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_1uiv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI1uiv(GLuint        index,
                                             const GLuint* v)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    /* TODO: Make me more useful */
    AI_TRACE("glVertexAttribI1uiv(index=[%u] v=[%p])",
             index,
             v);

    reinterpret_cast<PFNGLVERTEXATTRIBI1UIVPROC>(OpenGL::g_cached_gl_vertex_attrib_i_1uiv)(index,
                                                                                           v);
}
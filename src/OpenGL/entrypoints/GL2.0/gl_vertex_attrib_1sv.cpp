/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1sv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib1sv(GLuint         index,
                                           const GLshort* v)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    /* TODO: Make me more useful */
    AI_TRACE("glVertexAttrib1sv(index=[%u] v=[%p])",
             index,
             v);

    reinterpret_cast<PFNGLVERTEXATTRIB1SVPROC>(OpenGL::g_cached_gl_vertex_attrib_1sv)(index,
                                                                                      v);
}
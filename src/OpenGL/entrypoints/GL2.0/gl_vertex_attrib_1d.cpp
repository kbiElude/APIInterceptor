/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1d.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib1d(GLuint   index,
                                          GLdouble x)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glVertexAttrib1d(index=[%u] x=[%.4f])",
             index,
             static_cast<float>(x) );

    reinterpret_cast<PFNGLVERTEXATTRIB1DPROC>(OpenGL::g_cached_gl_vertex_attrib_1d)(index,
                                                                                    x);
}
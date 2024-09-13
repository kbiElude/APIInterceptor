/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4d.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib4d(GLuint   index,
                                          GLdouble x,
                                          GLdouble y,
                                          GLdouble z,
                                          GLdouble w)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glVertexAttrib4d(index=[%u] x=[%.4f] y=[%.4f] z=[%.4f] w=[%.4f])",
             index,
             static_cast<float>(x),
             static_cast<float>(y),
             static_cast<float>(z),
             static_cast<float>(w) );

    reinterpret_cast<PFNGLVERTEXATTRIB4DPROC>(OpenGL::g_cached_gl_vertex_attrib_4d)(index,
                                                                                    x,
                                                                                    y,
                                                                                    z,
                                                                                    w);
}
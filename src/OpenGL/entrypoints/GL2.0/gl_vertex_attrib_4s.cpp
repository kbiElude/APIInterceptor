/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4s.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib4s(GLuint  index,
                                          GLshort x,
                                          GLshort y,
                                          GLshort z,
                                          GLshort w)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glVertexAttrib4s(index=[%u] x=[%d] y=[%d] z=[%d] w=[%d])",
             index,
             static_cast<int32_t>(x),
             static_cast<int32_t>(y),
             static_cast<int32_t>(z),
             static_cast<int32_t>(w) );

    reinterpret_cast<PFNGLVERTEXATTRIB4SPROC>(OpenGL::g_cached_gl_vertex_attrib_4s)(index,
                                                                                    x,
                                                                                    y,
                                                                                    z,
                                                                                    w);
}
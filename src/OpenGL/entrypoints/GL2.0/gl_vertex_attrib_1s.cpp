/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1s.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib1s(GLuint  index,
                                          GLshort x)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glVertexAttrib1s(index=[%u] x=[%d])",
               index,
               static_cast<int32_t>(x) );

    reinterpret_cast<PFNGLVERTEXATTRIB1SPROC>(OpenGL::g_cached_gl_vertex_attrib_1s)(index,
                                                                                    x);
}
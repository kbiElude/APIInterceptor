/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nub.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib4Nub(GLuint  index,
                                            GLubyte x,
                                            GLubyte y,
                                            GLubyte z,
                                            GLubyte w)
{
    AI_TRACE("glVertexAttrib4Nub(index=[%u] x=[%u] y=[%u] z=[%u] w=[%u])",
             index,
             static_cast<uint32_t>(x),
             static_cast<uint32_t>(y),
             static_cast<uint32_t>(z),
             static_cast<uint32_t>(w) );

    if (OpenGL::g_cached_gl_vertex_attrib_4Nub == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_4Nub = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttrib4Nub");
    }

    reinterpret_cast<PFNGLVERTEXATTRIB4NUBPROC>(OpenGL::g_cached_gl_vertex_attrib_4Nub)(index,
                                                                                        x,
                                                                                        y,
                                                                                        z,
                                                                                        w);
}
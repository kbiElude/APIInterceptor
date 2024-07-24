/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2s.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib2s(GLuint  index,
                                          GLshort x,
                                          GLshort y)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glVertexAttrib2s(index=[%u] x=[%d] y=[%d])",
             index,
             static_cast<int32_t>(x),
             static_cast<int32_t>(y) );

    if (OpenGL::g_cached_gl_vertex_attrib_2s == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_2s = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttrib2s");
    }

    reinterpret_cast<PFNGLVERTEXATTRIB2SPROC>(OpenGL::g_cached_gl_vertex_attrib_2s)(index,
                                                                                    x,
                                                                                    y);
}
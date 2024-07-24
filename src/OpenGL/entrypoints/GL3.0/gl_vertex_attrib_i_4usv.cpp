/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4usv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI4usv(GLuint          index,
                                             const GLushort* v)
{
    /* TODO: Make me more useful */
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glVertexAttribI4usv(index=[%u] v=[%p])",
             index,
             v);

    if (OpenGL::g_cached_gl_vertex_attrib_i_4usv == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_i_4usv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttribI4usv");
    }

    reinterpret_cast<PFNGLVERTEXATTRIBI4USVPROC>(OpenGL::g_cached_gl_vertex_attrib_i_4usv)(index,
                                                                                           v);
}
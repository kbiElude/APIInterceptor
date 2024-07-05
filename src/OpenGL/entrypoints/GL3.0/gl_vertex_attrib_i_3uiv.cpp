/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3uiv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI3uiv(GLuint        index,
                                             const GLuint* v)
{
    /* TODO: Make me more useful */
    AI_TRACE("glVertexAttribI3uiv(index=[%u] v=[%p])",
             index,
             v);

    if (OpenGL::g_cached_gl_vertex_attrib_i_3uiv == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_i_3uiv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttribI3uiv");
    }

    reinterpret_cast<PFNGLVERTEXATTRIBI3UIVPROC>(OpenGL::g_cached_gl_vertex_attrib_i_3uiv)(index,
                                                                                           v);
}
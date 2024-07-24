/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_2uiv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI2uiv(GLuint        index,
                                             const GLuint* v)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    /* TODO: Make me more useful */
    AI_TRACE("glVertexAttribI2uiv(index=[%u] v=[%p])",
             index,
             v);

    if (OpenGL::g_cached_gl_vertex_attrib_i_2uiv == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_i_2uiv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttribI2uiv");
    }

    reinterpret_cast<PFNGLVERTEXATTRIBI2UIVPROC>(OpenGL::g_cached_gl_vertex_attrib_i_2uiv)(index,
                                                                                           v);
}
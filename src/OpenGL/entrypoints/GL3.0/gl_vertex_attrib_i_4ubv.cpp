/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4ubv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI4ubv(GLuint         index,
                                             const GLubyte* v)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    /* TODO: Make me more useful */
    AI_TRACE("glVertexAttribI4ubv(index=[%u] v=[%p])",
             index,
             v);

    if (OpenGL::g_cached_gl_vertex_attrib_i_4ubv == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_i_4ubv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttribI4ubv");
    }

    reinterpret_cast<PFNGLVERTEXATTRIBI4UBVPROC>(OpenGL::g_cached_gl_vertex_attrib_i_4ubv)(index,
                                                                                           v);
}
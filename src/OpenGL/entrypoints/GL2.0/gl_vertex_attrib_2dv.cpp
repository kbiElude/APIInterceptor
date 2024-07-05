/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2dv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib2dv(GLuint          index,
                                           const GLdouble* v)
{
    /* TODO: Make me more useful */
    AI_TRACE("glVertexAttriv2dv(index=[%u] v=[%p])",
             index,
             v);

    if (OpenGL::g_cached_gl_vertex_attrib_2dv == nullptr)
    {
        OpenGL::g_cached_gl_vertex_attrib_2dv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glVertexAttriv2dv");
    }

    reinterpret_cast<PFNGLVERTEXATTRIB2DVPROC>(OpenGL::g_cached_gl_vertex_attrib_2dv)(index,
                                                                                      v);
}
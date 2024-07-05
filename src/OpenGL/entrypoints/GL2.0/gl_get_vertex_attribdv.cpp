/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_get_vertex_attribdv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetVertexAttribdv(GLuint    index,
                                             GLenum    pname,
                                             GLdouble* params)
{
    AI_TRACE("glGetVertexAttribdv(index=[%u] pname=[%s] params=[%p])",
             index,
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_get_vertex_attribdv == nullptr)
    {
        OpenGL::g_cached_gl_get_vertex_attribdv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetVertexAttribdv");
    }

    reinterpret_cast<PFNGLGETVERTEXATTRIBDVPROC>(OpenGL::g_cached_gl_get_vertex_attribdv)(index,
                                                                                          pname,
                                                                                          params);
}
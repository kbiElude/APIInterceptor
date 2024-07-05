/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_get_vertex_attribfv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetVertexAttribfv(GLuint   index,
                                             GLenum   pname,
                                             GLfloat* params)
{
    AI_TRACE("glGetVertexAttribfv(index=[%u] pname=[%s] params=[%p])",
             index,
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_get_vertex_attribfv == nullptr)
    {
        OpenGL::g_cached_gl_get_vertex_attribfv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetVertexAttribfv");
    }

    reinterpret_cast<PFNGLGETVERTEXATTRIBFVPROC>(OpenGL::g_cached_gl_get_vertex_attribfv)(index,
                                                                                          pname,
                                                                                          params);
}
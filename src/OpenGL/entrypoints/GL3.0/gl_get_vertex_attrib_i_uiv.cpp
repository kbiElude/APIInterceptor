/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_get_vertex_attrib_i_uiv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetVertexAttribIuiv(GLuint  index,
                                               GLenum  pname,
                                               GLuint* params)
{
    AI_TRACE("glGetVertexAttribIuiv(index=[%u] pname=[%s] params=[%p])",
             index,
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_get_vertex_attrib_i_uiv == nullptr)
    {
        OpenGL::g_cached_gl_get_vertex_attrib_i_uiv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetVertexAttribIuiv");
    }

    reinterpret_cast<PFNGLGETVERTEXATTRIBIUIVPROC>(OpenGL::g_cached_gl_get_vertex_attrib_i_uiv)(index,
                                                                                                pname,
                                                                                                params);
}
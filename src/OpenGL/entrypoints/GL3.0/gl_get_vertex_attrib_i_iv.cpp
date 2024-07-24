/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_get_vertex_attrib_i_iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetVertexAttribIiv(GLuint index,
                                              GLenum pname,
                                              GLint* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetVertexAttribIiv(index=[%u] pname=[%s] params=[%p])",
             index,
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_get_vertex_attrib_i_iv == nullptr)
    {
        OpenGL::g_cached_gl_get_vertex_attrib_i_iv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetVertexAttribIiv");
    }

    reinterpret_cast<PFNGLGETVERTEXATTRIBIIVPROC>(OpenGL::g_cached_gl_get_vertex_attrib_i_iv)(index,
                                                                                              pname,
                                                                                              params);
}
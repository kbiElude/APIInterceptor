/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_enable_vertex_attrib_array.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEnableVertexAttribArray(GLuint index)
{
    AI_TRACE("glEnableVertexAttribArray(index=[%u])",
             index);

    if (OpenGL::g_cached_gl_enable_vertex_attrib_array == nullptr)
    {
        OpenGL::g_cached_gl_enable_vertex_attrib_array = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glEnableVertexAttribArray");
    }

    reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(OpenGL::g_cached_gl_enable_vertex_attrib_array)(index);
}
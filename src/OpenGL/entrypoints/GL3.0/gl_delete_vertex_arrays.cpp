/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_delete_vertex_arrays.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDeleteVertexArrays(GLsizei       n,
                                              const GLuint* arrays)
{
    AI_TRACE("glDeleteVertexArrays(n=[%d] arrays=[%p])",
             static_cast<int32_t>(n),
             arrays);

    if (OpenGL::g_cached_gl_delete_vertex_arrays == nullptr)
    {
        OpenGL::g_cached_gl_delete_vertex_arrays = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDeleteVertexArrays");
    }

    reinterpret_cast<PFNGLDELETEVERTEXARRAYSPROC>(OpenGL::g_cached_gl_delete_vertex_arrays)(n,
                                                                                            arrays);
}
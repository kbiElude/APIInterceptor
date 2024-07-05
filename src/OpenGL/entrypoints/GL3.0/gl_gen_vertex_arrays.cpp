/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_gen_vertex_arrays.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGenVertexArrays(GLsizei n,
                                           GLuint* arrays)
{
    AI_TRACE("glGenVertexArrays(n=[%d] arrays=[%p])",
             static_cast<int32_t>(n),
             arrays);

    if (OpenGL::g_cached_gl_gen_vertex_arrays == nullptr)
    {
        OpenGL::g_cached_gl_gen_vertex_arrays = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGenVertexArrays");
    }

    reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>(OpenGL::g_cached_gl_gen_vertex_arrays)(n,
                                                                                      arrays);
}
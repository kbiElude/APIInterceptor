/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_is_vertex_array.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsVertexArray(GLuint array)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glIsVertexArray(array=[%u])",
             array);

    if (OpenGL::g_cached_gl_is_vertex_array == nullptr)
    {
        OpenGL::g_cached_gl_is_vertex_array = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glIsVertexArray");
    }

    return reinterpret_cast<PFNGLISVERTEXARRAYPROC>(OpenGL::g_cached_gl_is_vertex_array)(array);
}
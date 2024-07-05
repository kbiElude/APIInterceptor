/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_uniform_2iv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniform2iv(GLint        location,
                                      GLsizei      count,
                                      const GLint* value)
{
    /* TODO: Make me more useful */
    AI_TRACE("glUniform2iv(location=[%d] count=[%d] value=[%p])",
             location,
             static_cast<int32_t>(count),
             value);

    if (OpenGL::g_cached_gl_uniform_2iv == nullptr)
    {
        OpenGL::g_cached_gl_uniform_2iv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glUniform2iv");
    }

    reinterpret_cast<PFNGLUNIFORM2IVPROC>(OpenGL::g_cached_gl_uniform_2iv)(location,
                                                                           count,
                                                                           value);
}
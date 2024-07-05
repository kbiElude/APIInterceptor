/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_uniform_2fv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniform2fv(GLint          location,
                                      GLsizei        count,
                                      const GLfloat* value)
{
    /* TODO: Make me more useful */
    AI_TRACE("glUniform2fv(location=[%d] count=[%d] value=[%p])",
             location,
             static_cast<int32_t>(count),
             value);

    if (OpenGL::g_cached_gl_uniform_2fv == nullptr)
    {
        OpenGL::g_cached_gl_uniform_2fv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glUniform2fv");
    }

    reinterpret_cast<PFNGLUNIFORM2FVPROC>(OpenGL::g_cached_gl_uniform_2fv)(location,
                                                                           count,
                                                                           value);
}
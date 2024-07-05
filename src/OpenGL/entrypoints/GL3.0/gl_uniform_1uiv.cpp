/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_uniform_1uiv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniform1uiv(GLint         location,
                                       GLsizei       count,
                                       const GLuint* value)
{
    /* TODO: Make me more useful */
    AI_TRACE("glUniform1uiv(location=[%d] count=[%d] value=[%p])",
             location,
             static_cast<int32_t>(count),
             value);

    if (OpenGL::g_cached_gl_uniform_1uiv == nullptr)
    {
        OpenGL::g_cached_gl_uniform_1uiv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glUniform1uiv");
    }

    reinterpret_cast<PFNGLUNIFORM1UIVPROC>(OpenGL::g_cached_gl_uniform_1uiv)(location,
                                                                             count,
                                                                             value);
}
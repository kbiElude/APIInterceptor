/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_is_shader.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsShader(GLuint shader)
{
    AI_TRACE("glIsShader(shader=[%u])",
             shader);

    if (OpenGL::g_cached_gl_is_shader == nullptr)
    {
        OpenGL::g_cached_gl_is_shader = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glIsShader");
    }

    return reinterpret_cast<PFNGLISSHADERPROC>(OpenGL::g_cached_gl_is_shader)(shader);
}

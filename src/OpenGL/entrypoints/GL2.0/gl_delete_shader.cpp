/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_delete_shader.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDeleteShader(GLuint shader)
{
    AI_TRACE("glDeleteShader(shader=[%d])",
             shader);

    if (OpenGL::g_cached_gl_delete_shader == nullptr)
    {
        OpenGL::g_cached_gl_delete_shader = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDeleteShader");
    }

    reinterpret_cast<PFNGLDELETESHADERPROC>(OpenGL::g_cached_gl_delete_shader)(shader);
}
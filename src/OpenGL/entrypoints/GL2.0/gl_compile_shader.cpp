/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_compile_shader.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCompileShader(GLuint shader)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glCompileShader(shader=[%d])",
             shader);

    if (OpenGL::g_cached_gl_compile_shader == nullptr)
    {
        OpenGL::g_cached_gl_compile_shader = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glCompileShader");
    }

    reinterpret_cast<PFNGLCOMPILESHADERPROC>(OpenGL::g_cached_gl_compile_shader)(shader);
}
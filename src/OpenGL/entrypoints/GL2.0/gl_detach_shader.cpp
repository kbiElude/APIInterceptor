/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_detach_shader.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDetachShader(GLuint program,
                                        GLuint shader)
{
    AI_TRACE("glDetachShader(program=[%d] shader=[%d])",
             program,
             shader);

    if (OpenGL::g_cached_gl_detach_shader == nullptr)
    {
        OpenGL::g_cached_gl_detach_shader = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDetachShader");
    }

    reinterpret_cast<PFNGLDETACHSHADERPROC>(OpenGL::g_cached_gl_detach_shader)(program,
                                                                               shader);
}
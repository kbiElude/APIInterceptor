/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_create_shader.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

GLuint AI_APIENTRY OpenGL::aiCreateShader(GLenum type)
{
    AI_TRACE("glCreateShader(type=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(type) );

    if (OpenGL::g_cached_gl_create_shader == nullptr)
    {
        OpenGL::g_cached_gl_create_shader = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glCreateShader");
    }

    return reinterpret_cast<PFNGLCREATESHADERPROC>(OpenGL::g_cached_gl_create_shader)(type);
}
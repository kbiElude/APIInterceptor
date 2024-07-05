/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.5/gl_is_buffer.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsBuffer(GLuint buffer)
{
    AI_TRACE("glIsBuffer(buffer=[%u])",
             buffer);

    if (OpenGL::g_cached_gl_is_buffer == nullptr)
    {
        OpenGL::g_cached_gl_is_buffer = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glIsBuffer");
    }

    return reinterpret_cast<PFNGLISBUFFERPROC>(OpenGL::g_cached_gl_is_buffer)(buffer);
}
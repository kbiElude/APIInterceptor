/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_is_framebuffer.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsFramebuffer(GLuint framebuffer)
{
    AI_TRACE("glIsFramebuffer(framebuffer=[%u])",
             framebuffer);

    if (OpenGL::g_cached_gl_is_framebuffer == nullptr)
    {
        OpenGL::g_cached_gl_is_framebuffer = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glIsFramebuffer");
    }

    return reinterpret_cast<PFNGLISFRAMEBUFFERPROC>(OpenGL::g_cached_gl_is_framebuffer)(framebuffer);
}
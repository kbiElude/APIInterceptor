/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_bind_framebuffer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBindFramebuffer(GLenum target,
                                           GLuint framebuffer)
{
    AI_TRACE("glBindFramebuffer(target=[%s] framebuffer=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             framebuffer);

    if (OpenGL::g_cached_gl_bind_framebuffer == nullptr)
    {
        OpenGL::g_cached_gl_bind_framebuffer = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glBindFramebuffer");
    }

    reinterpret_cast<PFNGLBINDFRAMEBUFFERPROC>(OpenGL::g_cached_gl_bind_framebuffer)(target,
                                                                                     framebuffer);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.2/gl_framebuffer_texture.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFramebufferTexture(GLenum target,
                                              GLenum attachment,
                                              GLuint texture,
                                              GLint  level)
{
    AI_TRACE("glFramebufferTexture(target=[%s] attachment=[%s] texture=[%u] level=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(attachment),
             texture,
             level);

    if (OpenGL::g_cached_gl_framebuffer_texture == nullptr)
    {
        OpenGL::g_cached_gl_framebuffer_texture = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glFramebufferTexture");
    }

    reinterpret_cast<PFNGLFRAMEBUFFERTEXTUREPROC>(OpenGL::g_cached_gl_framebuffer_texture)(target,
                                                                                          attachment,
                                                                                          texture,
                                                                                          level);
}
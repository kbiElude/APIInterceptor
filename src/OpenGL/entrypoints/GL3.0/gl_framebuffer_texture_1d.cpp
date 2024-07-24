/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_framebuffer_texture_1d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFramebufferTexture1D(GLenum target,
                                                GLenum attachment,
                                                GLenum textarget,
                                                GLuint texture,
                                                GLint  level)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glFramebufferTexture1D(target=[%s] attachment=[%s] textarget=[%s] texture=[%u] level=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(attachment),
             OpenGL::Utils::get_raw_string_for_gl_enum(textarget),
             texture,
             level);

    if (OpenGL::g_cached_gl_framebuffer_texture_1D == nullptr)
    {
        OpenGL::g_cached_gl_framebuffer_texture_1D = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glFramebufferTexture1D");
    }

    reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE1DPROC>(OpenGL::g_cached_gl_framebuffer_texture_1D)(target,
                                                                                                attachment,
                                                                                                textarget,
                                                                                                texture,
                                                                                                level);
}
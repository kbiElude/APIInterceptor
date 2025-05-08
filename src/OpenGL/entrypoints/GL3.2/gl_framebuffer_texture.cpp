/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.2/gl_framebuffer_texture.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFramebufferTexture(GLenum target,
                                              GLenum attachment,
                                              GLuint texture,
                                              GLint  level)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glFramebufferTexture(target=[%s] attachment=[%s] texture=[%u] level=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(attachment),
             texture,
             level);

    reinterpret_cast<PFNGLFRAMEBUFFERTEXTUREPROC>(OpenGL::g_cached_gl_framebuffer_texture)(target,
                                                                                          attachment,
                                                                                          texture,
                                                                                          level);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_framebuffer_texture_2d.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFramebufferTexture2D(GLenum target,
                                                GLenum attachment,
                                                GLenum textarget,
                                                GLuint texture,
                                                GLint  level)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glFramebufferTexture2D(target=[%s] attachment=[%s] textarget=[%s] texture=[%u] level=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(attachment),
             OpenGL::Utils::get_raw_string_for_gl_enum(textarget),
             texture,
             level);

    reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE2DPROC>(OpenGL::g_cached_gl_framebuffer_texture_2D)(target,
                                                                                                attachment,
                                                                                                textarget,
                                                                                                texture,
                                                                                                level);
}
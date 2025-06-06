/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_framebuffer_renderbuffer.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFramebufferRenderbuffer(GLenum target,
                                                   GLenum attachment,
                                                   GLenum renderbuffertarget,
                                                   GLuint renderbuffer)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glFramebufferRenderbuffer(target=[%s] attachment=[%s] renderbuffertarget=[%s] renderbuffer=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(attachment),
             OpenGL::Utils::get_raw_string_for_gl_enum(renderbuffertarget),
             renderbuffer);

    reinterpret_cast<PFNGLFRAMEBUFFERRENDERBUFFERPROC>(OpenGL::g_cached_gl_framebuffer_renderbuffer)(target,
                                                                                                     attachment,
                                                                                                     renderbuffertarget,
                                                                                                     renderbuffer);
}
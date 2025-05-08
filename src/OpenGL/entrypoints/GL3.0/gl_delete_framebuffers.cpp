/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_delete_framebuffers.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDeleteFramebuffers(GLsizei       n,
                                              const GLuint* framebuffers)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glDeleteFramebuffers(n=[%d] framebuffers=[%p])",
             static_cast<int32_t>(n),
             framebuffers);

    reinterpret_cast<PFNGLDELETEFRAMEBUFFERSPROC>(OpenGL::g_cached_gl_delete_framebuffers)(n,
                                                                                           framebuffers);
}
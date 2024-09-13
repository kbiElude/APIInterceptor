/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_gen_framebuffers.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGenFramebuffers(GLsizei n,
                                           GLuint* framebuffers)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGenFramebuffers(n=[%d] framebuffers=[%p])",
             static_cast<int32_t>(n),
             framebuffers);

    reinterpret_cast<PFNGLGENFRAMEBUFFERSPROC>(OpenGL::g_cached_gl_gen_framebuffers)(n,
                                                                                     framebuffers);
}
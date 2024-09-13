/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_gen_renderbuffers.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGenRenderbuffers(GLsizei n,
                                            GLuint* renderbuffers)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGenRenderbuffers(n=[%d] renderbuffers=[%p])",
             static_cast<int32_t>(n),
             renderbuffers);

    reinterpret_cast<PFNGLGENRENDERBUFFERSPROC>(OpenGL::g_cached_gl_gen_renderbuffers)(n,
                                                                                       renderbuffers);
}
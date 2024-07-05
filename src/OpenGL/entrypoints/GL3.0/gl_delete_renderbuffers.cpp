/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_delete_renderbuffers.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDeleteRenderbuffers(GLsizei       n,
                                               const GLuint* renderbuffers)
{
    AI_TRACE("glDeleteRenderbuffers(n=[%d] renderbuffers=[%p])",
             static_cast<int32_t>(n),
             renderbuffers);

    reinterpret_cast<PFNGLDELETERENDERBUFFERSPROC>(OpenGL::g_cached_gl_delete_renderbuffers)(n,
                                                                                             renderbuffers);
}
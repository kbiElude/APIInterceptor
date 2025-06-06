/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.5/gl_delete_buffers.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDeleteBuffers(GLsizei       n,
                                         const GLuint* buffers)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glDeleteBuffers(n=[%d] buffers=[%p])",
             static_cast<int32_t>(n),
             buffers);

    reinterpret_cast<PFNGLDELETEBUFFERSPROC>(OpenGL::g_cached_gl_delete_buffers)(n,
                                                                                 buffers);
}
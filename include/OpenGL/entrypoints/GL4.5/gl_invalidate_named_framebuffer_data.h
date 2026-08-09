/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_INVALIDATE_NAMED_FRAMEBUFFER_DATA_H
#define AI_GL_INVALIDATE_NAMED_FRAMEBUFFER_DATA_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiInvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments);
}

#endif /* AI_GL_INVALIDATE_NAMED_FRAMEBUFFER_DATA_H */

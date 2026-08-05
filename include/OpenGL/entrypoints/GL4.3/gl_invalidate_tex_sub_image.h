/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_INVALIDATE_TEX_SUB_IMAGE_H
#define AI_GL_INVALIDATE_TEX_SUB_IMAGE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
}

#endif /* AI_GL_INVALIDATE_TEX_SUB_IMAGE_H */

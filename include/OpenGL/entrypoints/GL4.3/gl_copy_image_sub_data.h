/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COPY_IMAGE_SUB_DATA_H
#define AI_GL_COPY_IMAGE_SUB_DATA_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
}

#endif /* AI_GL_COPY_IMAGE_SUB_DATA_H */

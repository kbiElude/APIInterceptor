/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GETN_TEX_IMAGE_H
#define AI_GL_GETN_TEX_IMAGE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels);
}

#endif /* AI_GL_GETN_TEX_IMAGE_H */

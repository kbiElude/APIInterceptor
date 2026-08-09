/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_TEXTURE_LEVEL_PARAMETERFV_H
#define AI_GL_GET_TEXTURE_LEVEL_PARAMETERFV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat* params);
}

#endif /* AI_GL_GET_TEXTURE_LEVEL_PARAMETERFV_H */

/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEXTURE_STORAGE1D_H
#define AI_GL_TEXTURE_STORAGE1D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiTextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width);
}

#endif /* AI_GL_TEXTURE_STORAGE1D_H */

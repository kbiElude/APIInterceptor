/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BIND_IMAGE_TEXTURE_H
#define AI_GL_BIND_IMAGE_TEXTURE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBindImageTexture(GLuint    unit,
                                        GLuint    texture,
                                        GLint     level,
                                        GLboolean layered,
                                        GLint     layer,
                                        GLenum    access,
                                        GLenum    format);
}

#endif /* AI_GL_BIND_IMAGE_TEXTURE_H */

/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_COMPRESSED_TEX_IMAGE_H
#define AI_GL_GET_COMPRESSED_TEX_IMAGE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetCompressedTexImage(GLenum target,
                                             GLint  level,
                                             void*  img);
}

#endif /* AI_GL_GET_COMPRESSED_TEX_IMAGE_H */
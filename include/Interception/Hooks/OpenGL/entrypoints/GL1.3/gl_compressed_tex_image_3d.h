/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COMPRESSED_TEX_IMAGE_3D_H
#define AI_GL_COMPRESSED_TEX_IMAGE_3D_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiCompressedTexImage3D(GLenum      target,
                                                    GLint       level,
                                                    GLenum      internalformat,
                                                    GLsizei     width,
                                                    GLsizei     height,
                                                    GLsizei     depth,
                                                    GLint       border,
                                                    GLsizei     imageSize,
                                                    const void* data);
        }
    }
}
#endif /* AI_GL_COMPRESSED_TEX_IMAGE_3D_H */
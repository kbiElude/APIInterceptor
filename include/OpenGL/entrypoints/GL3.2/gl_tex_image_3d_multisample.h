/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEX_IMAGE_3D_MULTISAMPLE_H
#define AI_GL_TEX_IMAGE_3D_MULTISAMPLE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiTexImage3DMultisample(GLenum    target,
                                             GLsizei   samples,
                                             GLenum    internalformat,
                                             GLsizei   width,
                                             GLsizei   height,
                                             GLsizei   depth,
                                             GLboolean fixedsamplelocations);
}

#endif /* AI_GL_TEX_IMAGE_3D_MULTISAMPLE_H */
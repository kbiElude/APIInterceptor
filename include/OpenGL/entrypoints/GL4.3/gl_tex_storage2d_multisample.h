/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEX_STORAGE2D_MULTISAMPLE_H
#define AI_GL_TEX_STORAGE2D_MULTISAMPLE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
}

#endif /* AI_GL_TEX_STORAGE2D_MULTISAMPLE_H */

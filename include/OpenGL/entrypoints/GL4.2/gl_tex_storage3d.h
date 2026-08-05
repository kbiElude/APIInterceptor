/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEX_STORAGE3D_H
#define AI_GL_TEX_STORAGE3D_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiTexStorage3D(GLenum  target,
                                    GLsizei levels,
                                    GLenum  internalformat,
                                    GLsizei width,
                                    GLsizei height,
                                    GLsizei depth);
}

#endif /* AI_GL_TEX_STORAGE3D_H */

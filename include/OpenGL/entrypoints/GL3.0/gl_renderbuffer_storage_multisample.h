/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_RENDERBUFFER_STORAGE_MULTISAMPLE_H
#define AI_GL_RENDERBUFFER_STORAGE_MULTISAMPLE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiRenderbufferStorageMultisample(GLenum  target,
                                                      GLsizei samples,
                                                      GLenum  internalformat,
                                                      GLsizei width,
                                                      GLsizei height);
}

#endif /* AI_GL_RENDERBUFFER_STORAGE_MULTISAMPLE_H */
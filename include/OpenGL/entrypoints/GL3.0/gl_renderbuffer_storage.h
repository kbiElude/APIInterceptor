/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_RENDERBUFFER_STORAGE_H
#define AI_GL_RENDERBUFFER_STORAGE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiRenderbufferStorage(GLenum  target,
                                           GLenum  internalformat,
                                           GLsizei width,
                                           GLsizei height);
}

#endif /* AI_GL_RENDERBUFFER_STORAGE_H */
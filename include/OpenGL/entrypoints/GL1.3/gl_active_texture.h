/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_ACTIVE_TEXTURE_H
#define AI_GL_ACTIVE_TEXTURE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiActiveTexture(GLenum texture);
}

#endif /* AI_GL_ACTIVE_TEXTURE_H */
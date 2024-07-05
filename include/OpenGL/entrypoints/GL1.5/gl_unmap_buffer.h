/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_UNMAP_BUFFER_H
#define AI_GL_UNMAP_BUFFER_H

#include "OpenGL/types.h"

namespace OpenGL
{
    GLboolean AI_APIENTRY aiUnmapBuffer(GLenum target);
}

#endif /* AI_GL_UNMAP_BUFFER_H */
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_CLIP_PLANE_H
#define AI_GL_CLIP_PLANE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiClipPlane(GLenum          plane,
                                 const GLdouble* equation);
}

#endif /* AI_GL_CLIP_PLANE_H */
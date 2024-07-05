/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_ROTATE_F_H
#define AI_GL_ROTATE_F_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiRotatef(GLfloat angle,
                               GLfloat x,
                               GLfloat y,
                               GLfloat z);
}

#endif /* AI_GL_ROTATE_F_H */
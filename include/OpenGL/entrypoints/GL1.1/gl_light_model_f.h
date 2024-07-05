/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_LIGHT_MODEL_F_H
#define AI_GL_LIGHT_MODEL_F_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiLightModelf(GLenum  pname,
                                   GLfloat param);
}

#endif /* AI_GL_LIGHT_MODEL_F_H */
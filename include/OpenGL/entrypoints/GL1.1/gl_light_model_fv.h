/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_LIGHT_MODEL_FV_H
#define AI_GL_LIGHT_MODEL_FV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiLightModelfv(GLenum         pname,
                                    const GLfloat* params);
}

#endif /* AI_GL_LIGHT_MODEL_FV_H */
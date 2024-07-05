/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEX_ENV_FV_H
#define AI_GL_TEX_ENV_FV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiTexEnvfv(GLenum         target,
                                GLenum         pname,
                                const GLfloat* params);
}

#endif /* AI_GL_TEX_ENV_FV_H */
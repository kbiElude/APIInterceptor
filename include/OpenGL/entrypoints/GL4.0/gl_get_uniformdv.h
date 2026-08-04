/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_UNIFORMDV_H
#define AI_GL_GET_UNIFORMDV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetUniformdv(GLuint program, GLint location, GLdouble* params);
}

#endif /* AI_GL_GET_UNIFORMDV_H */

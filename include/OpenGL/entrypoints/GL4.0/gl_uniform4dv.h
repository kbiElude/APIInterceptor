/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_UNIFORM4DV_H
#define AI_GL_UNIFORM4DV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiUniform4dv(GLint location, GLsizei count, const GLdouble* value);
}

#endif /* AI_GL_UNIFORM4DV_H */

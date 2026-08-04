/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_UNIFORM_MATRIX3X4DV_H
#define AI_GL_UNIFORM_MATRIX3X4DV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble* value);
}

#endif /* AI_GL_UNIFORM_MATRIX3X4DV_H */

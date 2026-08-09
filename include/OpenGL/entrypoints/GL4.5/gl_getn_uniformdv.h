/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GETN_UNIFORMDV_H
#define AI_GL_GETN_UNIFORMDV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble* params);
}

#endif /* AI_GL_GETN_UNIFORMDV_H */

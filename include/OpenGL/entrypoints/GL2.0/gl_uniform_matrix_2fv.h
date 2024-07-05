/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_UNIFORM_MATRIX_2FV_H
#define AI_GL_UNIFORM_MATRIX_2FV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiUniformMatrix2fv(GLint          location,
                                        GLsizei        count,
                                        GLboolean      transpose,
                                        const GLfloat* value);
}

#endif /* AI_GL_UNIFORM_MATRIX_2FV_H */
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_UNIFORM_MATRIX_3X4_FV_H
#define AI_GL_UNIFORM_MATRIX_3X4_FV_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiUniformMatrix3x4fv(GLint          location,
                                                  GLsizei        count,
                                                  GLboolean      transpose,
                                                  const GLfloat* value);
        }
    }
}

#endif /* AI_GL_UNIFORM_MATRIX_3X4_FV_H */
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_UNIFORM_BLOCK_BINDING_H
#define AI_GL_UNIFORM_BLOCK_BINDING_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiUniformBlockBinding(GLuint program,
                                           GLuint uniformBlockIndex,
                                           GLuint uniformBlockBinding);
}

#endif /* AI_GL_UNIFORM_BLOCK_BINDING_H */
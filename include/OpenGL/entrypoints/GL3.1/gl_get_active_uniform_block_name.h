/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_ACTIVE_UNIFORM_BLOCK_NAME_H
#define AI_GL_GET_ACTIVE_UNIFORM_BLOCK_NAME_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetActiveUniformBlockName(GLuint   program,
                                                 GLuint   uniformBlockIndex,
                                                 GLsizei  bufSize,
                                                 GLsizei* length,
                                                 GLchar*  uniformBlockName);
}

#endif /* AI_GL_GET_ACTIVE_UNIFORM_BLOCK_NAME_H */
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_UNIFORM_INDICES_H
#define AI_GL_GET_UNIFORM_INDICES_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetUniformIndices(GLuint               program,
                                         GLsizei              uniformCount,
                                         const GLchar* const* uniformNames,
                                         GLuint*              uniformIndices);
}

#endif /* AI_GL_GET_UNIFORM_INDICES_H */
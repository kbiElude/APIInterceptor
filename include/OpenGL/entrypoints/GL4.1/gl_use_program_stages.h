/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_USE_PROGRAM_STAGES_H
#define AI_GL_USE_PROGRAM_STAGES_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program);
}

#endif /* AI_GL_USE_PROGRAM_STAGES_H */

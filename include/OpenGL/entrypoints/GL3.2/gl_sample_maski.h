/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_SAMPLE_MASKI_H
#define AI_GL_SAMPLE_MASKI_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiSampleMaski(GLuint     maskNumber,
                                   GLbitfield mask);
}

#endif /* AI_GL_SAMPLE_MASKI_H */
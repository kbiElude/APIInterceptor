/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BIND_FRAG_DATA_LOCATION_H
#define AI_GL_BIND_FRAG_DATA_LOCATION_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBindFragDataLocation(GLuint        program,
                                            GLuint        color,
                                            const GLchar* name);
}

#endif /* AI_GL_BIND_FRAG_DATA_LOCATION_H */
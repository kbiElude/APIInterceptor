/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_STRINGI_H
#define AI_GL_GET_STRINGI_H

#include "OpenGL/types.h"

namespace OpenGL
{
    const GLubyte *APIENTRY aiGetStringi(GLenum name,
                                         GLuint index);
}

#endif /* AI_GL_GET_STRINGI_H */
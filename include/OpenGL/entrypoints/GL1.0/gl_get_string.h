/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_STRING_H
#define AI_GL_GET_STRING_H

#include "OpenGL/types.h"

namespace OpenGL
{
    const GLubyte *APIENTRY aiGetString(GLenum name);
}

#endif /* AI_GL_GET_STRING_H */
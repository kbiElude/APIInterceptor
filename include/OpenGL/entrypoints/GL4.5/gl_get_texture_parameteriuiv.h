/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_TEXTURE_PARAMETERIUIV_H
#define AI_GL_GET_TEXTURE_PARAMETERIUIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint* params);
}

#endif /* AI_GL_GET_TEXTURE_PARAMETERIUIV_H */

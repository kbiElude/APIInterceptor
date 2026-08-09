/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_TEXTURE_PARAMETERIIV_H
#define AI_GL_GET_TEXTURE_PARAMETERIIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetTextureParameterIiv(GLuint texture, GLenum pname, GLint* params);
}

#endif /* AI_GL_GET_TEXTURE_PARAMETERIIV_H */

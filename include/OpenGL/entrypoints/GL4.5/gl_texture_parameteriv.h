/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEXTURE_PARAMETERIV_H
#define AI_GL_TEXTURE_PARAMETERIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiTextureParameteriv(GLuint texture, GLenum pname, const GLint* param);
}

#endif /* AI_GL_TEXTURE_PARAMETERIV_H */

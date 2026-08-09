/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEXTURE_PARAMETERIUIV_H
#define AI_GL_TEXTURE_PARAMETERIUIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiTextureParameterIuiv(GLuint texture, GLenum pname, const GLuint* params);
}

#endif /* AI_GL_TEXTURE_PARAMETERIUIV_H */

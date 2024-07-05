/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEX_GEN_I_H
#define AI_GL_TEX_GEN_I_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiTexGeni(GLenum coord,
                               GLenum pname,
                               GLint  param);
}

#endif /* AI_GL_TEX_GEN_I_H */
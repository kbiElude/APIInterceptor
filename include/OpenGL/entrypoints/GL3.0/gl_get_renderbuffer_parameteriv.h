/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_RENDERBUFFER_PARAMETERIV_H
#define AI_GL_GET_RENDERBUFFER_PARAMETERIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetRenderbufferParameteriv(GLenum target,
                                                  GLenum pname,
                                                  GLint* params);
}

#endif /* AI_GL_GET_RENDERBUFFER_PARAMETERIV_H */
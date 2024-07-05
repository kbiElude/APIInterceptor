/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_STENCIL_OP_H
#define AI_GL_STENCIL_OP_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiStencilOp(GLenum fail,
                                 GLenum zfail,
                                 GLenum zpass);
}

#endif /* AI_GL_STENCIL_OP_H */
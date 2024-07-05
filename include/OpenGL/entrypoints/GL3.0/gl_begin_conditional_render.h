/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BEGIN_CONDITIONAL_RENDER_H
#define AI_GL_BEGIN_CONDITIONAL_RENDER_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBeginConditionalRender(GLuint id,
                                              GLenum mode);
}

#endif /* AI_GL_BEGIN_CONDITIONAL_RENDER_H */
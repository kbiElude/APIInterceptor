/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BLEND_FUNC_H
#define AI_GL_BLEND_FUNC_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBlendFunc(GLenum sfactor,
                                 GLenum dfactor);
}

#endif /* AI_GL_BLEND_FUNC_H */
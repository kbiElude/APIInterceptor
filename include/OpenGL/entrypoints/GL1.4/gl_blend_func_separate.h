/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BLEND_FUNC_SEPARATE_H
#define AI_GL_BLEND_FUNC_SEPARATE_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBlendFuncSeparate(GLenum sfactorRGB,
                                         GLenum dfactorRGB,
                                         GLenum sfactorAlpha,
                                         GLenum dfactorAlpha);
}

#endif /* AI_GL_BLEND_FUNC_SEPARATE_H */
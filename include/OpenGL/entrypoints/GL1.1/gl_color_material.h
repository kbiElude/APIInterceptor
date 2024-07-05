/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COLOR_MATERIAL_H
#define AI_GL_COLOR_MATERIAL_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiColorMaterial(GLenum face,
                                     GLenum mode);
}

#endif /* AI_GL_COLOR_MATERIAL_H */
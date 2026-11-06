/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BLEND_EQUATION_SEPARATEI_H
#define AI_GL_BLEND_EQUATION_SEPARATEI_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiBlendEquationSeparatei(GLuint buf,
                                                      GLenum modeRGB,
                                                      GLenum modeAlpha);
        }
    }
}

#endif /* AI_GL_BLEND_EQUATION_SEPARATEI_H */

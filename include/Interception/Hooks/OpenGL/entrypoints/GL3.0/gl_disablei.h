/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DISABLEI_H
#define AI_GL_DISABLEI_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiDisablei(GLenum target,
                                        GLuint index);
        }
    }
}

#endif /* AI_GL_DISABLEI_H */
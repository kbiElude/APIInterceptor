/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_CLEAR_NAMED_FRAMEBUFFERFV_H
#define AI_GL_CLEAR_NAMED_FRAMEBUFFERFV_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiClearNamedFramebufferfv(GLuint         framebuffer,
                                                       GLenum         buffer,
                                                       GLint          drawbuffer,
                                                       const GLfloat* value);
        }
    }
}

#endif /* AI_GL_CLEAR_NAMED_FRAMEBUFFERFV_H */

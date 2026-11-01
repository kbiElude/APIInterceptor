/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_PIXEL_MAP_FV_H
#define AI_GL_PIXEL_MAP_FV_H

#include "Interception/Hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiPixelMapfv(GLenum         map,
                                          GLsizei        mapsize,
                                          const GLfloat* values);
        }
    }
}

#endif /* AI_GL_PIXEL_MAP_FV_H */
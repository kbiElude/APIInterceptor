/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_RASTER_POS_2F_H
#define AI_GL_RASTER_POS_2F_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiRasterPos2f(GLfloat x,
                                           GLfloat y);
        }
    }
}

#endif /* AI_GL_RASTER_POS_2F_H */
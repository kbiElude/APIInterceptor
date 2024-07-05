/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_RASTER_POS_4S_H
#define AI_GL_RASTER_POS_4S_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiRasterPos4s(GLshort x,
                                   GLshort y,
                                   GLshort z,
                                   GLshort w);
}

#endif /* AI_GL_RASTER_POS_4S_H */
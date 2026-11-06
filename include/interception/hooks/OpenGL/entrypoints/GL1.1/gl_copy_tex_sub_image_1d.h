/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_COPY_TEX_SUB_IMAGE_1D_H
#define AI_GL_COPY_TEX_SUB_IMAGE_1D_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiCopyTexSubImage1D(GLenum  target,
                                                 GLint   level,
                                                 GLint   xoffset,
                                                 GLint   x,
                                                 GLint   y,
                                                 GLsizei width);
        }
    }
}

#endif /* AI_GL_COPY_TEX_SUB_IMAGE_1D_H */
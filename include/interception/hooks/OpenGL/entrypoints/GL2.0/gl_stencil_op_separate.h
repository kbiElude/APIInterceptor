/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_STENCIL_OP_SEPARATE_H
#define AI_GL_STENCIL_OP_SEPARATE_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiStencilOpSeparate(GLenum face,
                                                 GLenum sfail,
                                                 GLenum dpfail,
                                                 GLenum dppass);
        }
    }
}

#endif /* AI_GL_STENCIL_OP_SEPARATE_H */
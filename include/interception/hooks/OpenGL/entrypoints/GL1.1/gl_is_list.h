/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_IS_LIST_H
#define AI_GL_IS_LIST_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            GLboolean AI_APIENTRY aiIsList(GLuint list);
        }
    }
}

#endif /* AI_GL_IS_LIST_H */
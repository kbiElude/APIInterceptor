/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_EVAL_POINT2_H
#define AI_GL_EVAL_POINT2_H

#include "interception/hooks/OpenGL/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            void AI_APIENTRY aiEvalPoint2(GLint i,
                                          GLint j);
        }
    }
}

#endif /* AI_GL_EVAL_POINT2_H */
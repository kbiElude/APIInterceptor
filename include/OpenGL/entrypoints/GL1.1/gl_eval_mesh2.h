/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_EVAL_MESH2_H
#define AI_GL_EVAL_MESH2_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiEvalMesh2(GLenum mode,
                                 GLint  i1,
                                 GLint  i2,
                                 GLint  j1,
                                 GLint  j2);
}

#endif /* AI_GL_EVAL_MESH2_H */
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_PATCH_PARAMETERFV_H
#define AI_GL_PATCH_PARAMETERFV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiPatchParameterfv(GLenum pname, const GLfloat* values);
}

#endif /* AI_GL_PATCH_PARAMETERFV_H */

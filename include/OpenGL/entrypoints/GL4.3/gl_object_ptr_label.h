/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_OBJECT_PTR_LABEL_H
#define AI_GL_OBJECT_PTR_LABEL_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiObjectPtrLabel(const void* ptr, GLsizei length, const GLchar* label);
}

#endif /* AI_GL_OBJECT_PTR_LABEL_H */

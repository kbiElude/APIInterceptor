/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_OBJECT_PTR_LABEL_H
#define AI_GL_GET_OBJECT_PTR_LABEL_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetObjectPtrLabel(const void* ptr, GLsizei bufSize, GLsizei* length, GLchar* label);
}

#endif /* AI_GL_GET_OBJECT_PTR_LABEL_H */

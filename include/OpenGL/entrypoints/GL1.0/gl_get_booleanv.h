/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_BOOLEANV_H
#define AI_GL_GET_BOOLEANV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetBooleanv(GLenum     pname,
                                   GLboolean* data);
}

#endif /* AI_GL_GET_BOOLEANV_H */
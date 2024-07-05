/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_MULTISAMPLEFV_H
#define AI_GL_GET_MULTISAMPLEFV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetMultisamplefv(GLenum   pname,
                                        GLuint   index,
                                        GLfloat* val);
}

#endif /* AI_GL_GET_MULTISAMPLEFV_H */
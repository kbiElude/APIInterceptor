/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_GET_TEX_PARAMETER_I_UIV_H
#define AI_GL_GET_TEX_PARAMETER_I_UIV_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiGetTexParameterIuiv(GLenum  target,
                                           GLenum  pname,
                                           GLuint* params);
}

#endif /* AI_GL_GET_TEX_PARAMETER_I_UIV_H */
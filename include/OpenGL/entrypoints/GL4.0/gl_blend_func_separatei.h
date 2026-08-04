/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_BLEND_FUNC_SEPARATEI_H
#define AI_GL_BLEND_FUNC_SEPARATEI_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
}

#endif /* AI_GL_BLEND_FUNC_SEPARATEI_H */

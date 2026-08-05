/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_TEXTURE_VIEW_H
#define AI_GL_TEXTURE_VIEW_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
}

#endif /* AI_GL_TEXTURE_VIEW_H */

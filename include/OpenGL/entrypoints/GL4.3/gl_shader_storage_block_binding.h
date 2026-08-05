/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_SHADER_STORAGE_BLOCK_BINDING_H
#define AI_GL_SHADER_STORAGE_BLOCK_BINDING_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
}

#endif /* AI_GL_SHADER_STORAGE_BLOCK_BINDING_H */

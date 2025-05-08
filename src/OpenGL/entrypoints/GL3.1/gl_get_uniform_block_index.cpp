/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.1/gl_get_uniform_block_index.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLuint AI_APIENTRY OpenGL::aiGetUniformBlockIndex(GLuint        program,
                                                  const GLchar* uniformBlockName)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetUniformBlockIndex(program=[%u] uniformBlockName=[%s])",
             program,
             uniformBlockName);

    return reinterpret_cast<PFNGLGETUNIFORMBLOCKINDEXPROC>(OpenGL::g_cached_gl_get_uniform_block_index)(program,
                                                                                                        uniformBlockName);
}
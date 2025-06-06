/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.1/gl_get_active_uniform_block_name.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetActiveUniformBlockName(GLuint   program,
                                                     GLuint   uniformBlockIndex,
                                                     GLsizei  bufSize,
                                                     GLsizei* length,
                                                     GLchar*  uniformBlockName)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetActiveUniformBlockName(program=[%u] uniformBlockIndex=[%u] bufSize=[%d] length=[%p] uniformBlockName=[%p])",
             program,
             uniformBlockIndex,
             static_cast<int32_t>(bufSize),
             length,
             uniformBlockName);

    reinterpret_cast<PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC>(OpenGL::g_cached_gl_get_active_uniform_block_name)(program,
                                                                                                            uniformBlockIndex,
                                                                                                            bufSize,
                                                                                                            length,
                                                                                                            uniformBlockName);
}
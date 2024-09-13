/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.1/gl_uniform_block_binding.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniformBlockBinding(GLuint program,
                                               GLuint uniformBlockIndex,
                                               GLuint uniformBlockBinding)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glUniformBlockBinding(program=[%u] uniformBlockIndex=[%u] uniformBlockBinding=[%u])",
             program,
             uniformBlockIndex,
             uniformBlockBinding);

    reinterpret_cast<PFNGLUNIFORMBLOCKBINDINGPROC>(OpenGL::g_cached_gl_uniform_block_binding)(program,
                                                                                              uniformBlockIndex,
                                                                                              uniformBlockBinding);
}
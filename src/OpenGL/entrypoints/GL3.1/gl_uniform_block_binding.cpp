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
    AI_TRACE("glUniformBlockBinding(program=[%u] uniformBlockIndex=[%u] uniformBlockBinding=[%u])",
             program,
             uniformBlockIndex,
             uniformBlockBinding);

    if (OpenGL::g_cached_gl_uniform_block_binding == nullptr)
    {
        OpenGL::g_cached_gl_uniform_block_binding = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glUniformBlockBinding");
    }

    reinterpret_cast<PFNGLUNIFORMBLOCKBINDINGPROC>(OpenGL::g_cached_gl_uniform_block_binding)(program,
                                                                                              uniformBlockIndex,
                                                                                              uniformBlockBinding);
}
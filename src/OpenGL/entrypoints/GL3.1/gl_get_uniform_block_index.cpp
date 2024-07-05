/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.1/gl_get_uniform_block_index.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLuint AI_APIENTRY OpenGL::aiGetUniformBlockIndex(GLuint        program,
                                                  const GLchar* uniformBlockName)
{
    AI_TRACE("glGetUniformBlockIndex(program=[%u] uniformBlockName=[%s])",
             program,
             uniformBlockName);

    if (OpenGL::g_cached_gl_end_transform_feedback == nullptr)
    {
        OpenGL::g_cached_gl_end_transform_feedback = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glEndTransformFeedback");
    }

    return reinterpret_cast<PFNGLGETUNIFORMBLOCKINDEXPROC>(OpenGL::g_cached_gl_get_uniform_block_index)(program,
                                                                                                        uniformBlockName);
}
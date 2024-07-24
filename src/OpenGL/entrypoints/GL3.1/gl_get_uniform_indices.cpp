/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.1/gl_get_uniform_indices.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetUniformIndices(GLuint               program,
                                             GLsizei              uniformCount,
                                             const GLchar* const* uniformNames,
                                             GLuint*              uniformIndices)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    /* TODO: Make me more useful */
    AI_TRACE("glGetUniformIndices(program=[%u] uniformCount=[%d] uniformNames=[%p] uniformIndices=[%p])",
             program,
             static_cast<int32_t>(uniformCount),
             uniformNames,
             uniformIndices);

    if (OpenGL::g_cached_gl_get_uniform_indices == nullptr)
    {
        OpenGL::g_cached_gl_get_uniform_indices = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetUniformIndices");
    }

    reinterpret_cast<PFNGLGETUNIFORMINDICESPROC>(OpenGL::g_cached_gl_get_uniform_indices)(program,
                                                                                          uniformCount,
                                                                                          uniformNames,
                                                                                          uniformIndices);
}
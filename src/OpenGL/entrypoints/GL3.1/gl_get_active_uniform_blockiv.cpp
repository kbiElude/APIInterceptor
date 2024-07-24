/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.1/gl_get_active_uniform_blockiv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetActiveUniformBlockiv(GLuint program,
                                                   GLuint uniformBlockIndex,
                                                   GLenum pname,
                                                   GLint* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetActiveUniformBlockiv(program=[%u] uniformBlockIndex=[%u] pname=[%s] params=[%p])",
             program,
             uniformBlockIndex,
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_get_active_uniform_blockiv == nullptr)
    {
        OpenGL::g_cached_gl_get_active_uniform_blockiv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetActiveUniformBlockiv");
    }

    reinterpret_cast<PFNGLGETACTIVEUNIFORMBLOCKIVPROC>(OpenGL::g_cached_gl_get_active_uniform_blockiv)(program,
                                                                                                       uniformBlockIndex,
                                                                                                       pname,
                                                                                                       params);
}
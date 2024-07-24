/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.1/gl_get_active_uniform_name.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetActiveUniformName(GLuint   program,
                                                GLuint   uniformIndex,
                                                GLsizei  bufSize,
                                                GLsizei* length,
                                                GLchar*  uniformName)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetActiveUniformName(program=[%u] uniformIndex=[%u] bufSize=[%d] length=[%p] uniformName=[%p])",
             program,
             uniformIndex,
             static_cast<int32_t>(bufSize),
             length,
             uniformName);

    if (OpenGL::g_cached_gl_end_transform_feedback == nullptr)
    {
        OpenGL::g_cached_gl_end_transform_feedback = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glEndTransformFeedback");
    }

    reinterpret_cast<PFNGLGETACTIVEUNIFORMNAMEPROC>(OpenGL::g_cached_gl_get_active_uniform_name)(program,
                                                                                                 uniformIndex,
                                                                                                 bufSize,
                                                                                                 length,
                                                                                                 uniformName);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_bind_buffer_base.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBindBufferBase(GLenum target,
                                          GLuint index,
                                          GLuint buffer)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glBindBufferBase(target=[%s] index=[%d] buffer=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             index,
             buffer);

    if (OpenGL::g_cached_gl_bind_buffer_base == nullptr)
    {
        OpenGL::g_cached_gl_bind_buffer_base = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glBindBufferBase");
    }

    reinterpret_cast<PFNGLBINDBUFFERBASEPROC>(OpenGL::g_cached_gl_bind_buffer_base)(target,
                                                                                    index,
                                                                                    buffer);
}
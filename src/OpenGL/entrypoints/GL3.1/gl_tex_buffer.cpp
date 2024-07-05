/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.1/gl_tex_buffer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexBuffer(GLenum target,
                                     GLenum internalformat,
                                     GLuint buffer)
{
    AI_TRACE("glTexBuffer(target=[%s] internalformat=[%s] buffer=[%u])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
             buffer);

    if (OpenGL::g_cached_gl_tex_buffer == nullptr)
    {
        OpenGL::g_cached_gl_tex_buffer = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glTexBuffer");
    }

    reinterpret_cast<PFNGLTEXBUFFERPROC>(g_cached_gl_tex_buffer)(target,
                                                                 internalformat,
                                                                 buffer);
}
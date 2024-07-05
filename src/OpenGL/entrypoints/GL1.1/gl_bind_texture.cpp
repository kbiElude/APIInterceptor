/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_bind_texture.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBindTexture(GLenum target,
                                       GLuint texture)
{
    AI_TRACE("glBindTexture(target=[%s] texture=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             texture);

    if (OpenGL::g_cached_gl_bind_texture == nullptr)
    {
        OpenGL::g_cached_gl_bind_texture = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glBindTexture");
    }

    reinterpret_cast<PFNGLBINDTEXTUREPROC>(OpenGL::g_cached_gl_bind_texture)(target,
                                                                             texture);
}
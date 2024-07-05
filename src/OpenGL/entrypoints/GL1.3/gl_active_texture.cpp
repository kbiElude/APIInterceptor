/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.3/gl_active_texture.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiActiveTexture(GLenum texture)
{
    AI_TRACE("glActiveTexture(texture=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(texture) );

    if (OpenGL::g_cached_gl_active_texture == nullptr)
    {
        OpenGL::g_cached_gl_active_texture = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glActiveTexture");
    }

    reinterpret_cast<PFNGLACTIVETEXTUREPROC>(OpenGL::g_cached_gl_active_texture)(texture);
}
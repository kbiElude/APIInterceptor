/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_generate_mipmap.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGenerateMipmap(GLenum target)
{
    AI_TRACE("glGenerateMipmap(target=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target) );

    if (OpenGL::g_cached_gl_generate_mipmap == nullptr)
    {
        OpenGL::g_cached_gl_generate_mipmap = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGenerateMipmap");
    }

    reinterpret_cast<PFNGLGENERATEMIPMAPPROC>(OpenGL::g_cached_gl_generate_mipmap)(target);
}
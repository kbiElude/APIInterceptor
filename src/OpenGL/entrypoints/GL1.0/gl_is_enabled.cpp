/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_is_enabled.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsEnabled(GLenum cap)
{
    AI_TRACE("glIsEnabled(cap=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(cap) );

    if (OpenGL::g_cached_gl_is_enabled == nullptr)
    {
        OpenGL::g_cached_gl_is_enabled = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glIsEnabled");
    }

    return reinterpret_cast<PFNGLISENABLEDPROC>(OpenGL::g_cached_gl_is_enabled)(cap);
}
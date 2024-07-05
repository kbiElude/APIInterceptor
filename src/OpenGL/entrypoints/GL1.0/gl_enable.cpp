/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_enable.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEnable(GLenum cap)
{
    AI_TRACE("glEnable(cap=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(cap) );

    if (OpenGL::g_cached_gl_enable == nullptr)
    {
        OpenGL::g_cached_gl_enable = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glEnable");
    }

    reinterpret_cast<PFNGLENABLEPROC>(OpenGL::g_cached_gl_enable)(cap);
}
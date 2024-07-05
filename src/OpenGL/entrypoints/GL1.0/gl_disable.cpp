/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_disable.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDisable(GLenum cap)
{
    AI_TRACE("glDisable(cap=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(cap) );

    if (OpenGL::g_cached_gl_disable == nullptr)
    {
        OpenGL::g_cached_gl_disable = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDisable");
    }

    reinterpret_cast<PFNGLDISABLEPROC>(OpenGL::g_cached_gl_disable)(cap);
}
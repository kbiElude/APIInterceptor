/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_hint.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiHint(GLenum target,
                                GLenum mode)
{
    AI_TRACE("glHint(target=[%s] mode=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(mode) );

    if (OpenGL::g_cached_gl_hint == nullptr)
    {
        OpenGL::g_cached_gl_hint = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glHint");
    }

    reinterpret_cast<PFNGLHINTPROC>(OpenGL::g_cached_gl_hint)(target,
                                                              mode);
}
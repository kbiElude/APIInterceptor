/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_read_buffer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiReadBuffer(GLenum src)
{
    AI_TRACE("glReadBuffer(src=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(src) );

    if (OpenGL::g_cached_gl_read_buffer == nullptr)
    {
        OpenGL::g_cached_gl_read_buffer = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glReadBuffer");
    }

    reinterpret_cast<PFNGLREADBUFFERPROC>(g_cached_gl_read_buffer)(src);
}
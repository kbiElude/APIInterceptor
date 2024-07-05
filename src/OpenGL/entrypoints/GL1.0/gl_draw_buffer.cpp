/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_draw_buffer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawBuffer(GLenum buf)
{
    AI_TRACE("glDrawBuffer(buf=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(buf) );

    if (OpenGL::g_cached_gl_draw_buffer == nullptr)
    {
        OpenGL::g_cached_gl_draw_buffer = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDrawBuffer");
    }

    reinterpret_cast<PFNGLDRAWBUFFERPROC>(OpenGL::g_cached_gl_draw_buffer)(buf);
}
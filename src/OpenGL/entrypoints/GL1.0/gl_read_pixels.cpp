/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_read_pixels.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiReadPixels(GLint   x,
                                      GLint   y,
                                      GLsizei width,
                                      GLsizei height,
                                      GLenum  format,
                                      GLenum  type,
                                      void*   pixels)
{
    AI_TRACE("glReadPixels(x=[%d] y=[%d] width=[%d] height=[%d] format=[%s] type=[%s] pixels=[%p])",
             x,
             y,
             static_cast<int32_t>(width),
             static_cast<int32_t>(height),
             OpenGL::Utils::get_raw_string_for_gl_enum(format),
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             pixels);

    if (OpenGL::g_cached_gl_read_pixels == nullptr)
    {
        OpenGL::g_cached_gl_read_pixels = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glReadPixels");
    }

    reinterpret_cast<PFNGLREADPIXELSPROC>(g_cached_gl_read_pixels)(x,
                                                                   y,
                                                                   width,
                                                                   height,
                                                                   format,
                                                                   type,
                                                                   pixels);
}
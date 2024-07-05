/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_draw_pixels.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawPixels(GLsizei       width,
                                      GLsizei       height,
                                      GLenum        format,
                                      GLenum        type,
                                      const GLvoid* pixels)
{
    AI_TRACE("glDrawPixels(width=[%d] height=[%d] format=[%s] type=[%s] pixels=[%p])",
             width,
             height,
             OpenGL::Utils::get_raw_string_for_gl_enum(format),
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             pixels);

    reinterpret_cast<PFNGLDRAWPIXELSPROC>(OpenGL::g_cached_gl_draw_pixels)(width,
                                                                           height,
                                                                           format,
                                                                           type,
                                                                           pixels);
}
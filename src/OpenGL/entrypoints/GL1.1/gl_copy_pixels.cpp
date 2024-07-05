/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_copy_pixels.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCopyPixels(GLint   x,
                                      GLint   y,
                                      GLsizei width,
                                      GLsizei height,
                                      GLenum  type)
{
    AI_TRACE("glCopyPixels(x=[%d] y=[%d] width=[%d] height=[%d] type=[%s])",
             x,
             y,
             width,
             height,
             OpenGL::Utils::get_raw_string_for_gl_enum(type) );

    reinterpret_cast<PFNGLCOPYPIXELSPROC>(OpenGL::g_cached_gl_copy_pixels)(x,
                                                                           y,
                                                                           width,
                                                                           height,
                                                                           type);
}
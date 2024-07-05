/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_get_pixel_map_usv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetPixelMapusv(GLenum    map,
                                          GLushort* values)
{
    AI_TRACE("glGetPixelMapusv(map=[%s], values=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(map),
             values);

    reinterpret_cast<PFNGLGETPIXELMAPUSVPROC>(OpenGL::g_cached_gl_pixel_map_usv)(map,
                                                                                 values);
}
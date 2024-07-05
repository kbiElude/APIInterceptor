/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_get_pixel_map_uiv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetPixelMapuiv(GLenum  map,
                                          GLuint* values)
{
    AI_TRACE("glGetPixelMapuiv(map=[%s], values=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(map),
             values);

    reinterpret_cast<PFNGLGETPIXELMAPUIVPROC>(OpenGL::g_cached_gl_get_pixel_map_uiv)(map,
                                                                                     values);
}
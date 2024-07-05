/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_pixel_map_uiv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPixelMapuiv(GLenum        map,
                                       GLsizei       mapsize,
                                       const GLuint* values)
{
    AI_TRACE("glPixelMapuiv(map=[%s], mapsize=[%d], values=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(map),
             mapsize,
             values);

    reinterpret_cast<PFNGLPIXELMAPUIVPROC>(OpenGL::g_cached_gl_pixel_map_uiv)(map,
                                                                              mapsize,
                                                                              values);
}
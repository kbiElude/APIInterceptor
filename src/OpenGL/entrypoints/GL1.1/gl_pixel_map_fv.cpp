/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_pixel_map_fv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPixelMapfv(GLenum        map,
                                      GLsizei        mapsize,
                                      const GLfloat* values)
{
    AI_TRACE("glPixelMapfv(map=[%s], mapsize=[%d], values=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(map),
             mapsize,
             values);

    reinterpret_cast<PFNGLPIXELMAPFVPROC>(OpenGL::g_cached_gl_pixel_map_fv)(map,
                                                                            mapsize,
                                                                            values);
}
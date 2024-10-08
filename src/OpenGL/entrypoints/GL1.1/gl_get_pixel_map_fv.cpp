/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_get_pixel_map_fv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetPixelMapfv(GLenum   map,
                                         GLfloat* values)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetPixelMapfv(map=[%s], values=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(map),
             values);

    reinterpret_cast<PFNGLGETPIXELMAPFVPROC>(OpenGL::g_cached_gl_get_pixel_map_fv)(map,
                                                                                   values);
}
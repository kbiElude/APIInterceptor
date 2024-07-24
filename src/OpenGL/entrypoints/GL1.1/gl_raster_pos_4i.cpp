/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_4i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos4i(GLint x,
                                       GLint y,
                                       GLint z,
                                       GLint w)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glRasterPos4i(x=[%d], y=[%d], z=[%d], w=[%d])",
             x,
             y,
             z,
             w);

    reinterpret_cast<PFNGLRASTERPOS4IPROC>(OpenGL::g_cached_gl_raster_pos_4i)(x,
                                                                              y,
                                                                              z,
                                                                              w);
}
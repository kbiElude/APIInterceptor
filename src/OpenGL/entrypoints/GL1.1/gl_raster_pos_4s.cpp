/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_4s.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos4s(GLshort x,
                                       GLshort y,
                                       GLshort z,
                                       GLshort w)
{
    AI_TRACE("glRasterPos4i(x=[%d], y=[%d], z=[%d], w=[%d])",
             static_cast<int32_t>(x),
             static_cast<int32_t>(y),
             static_cast<int32_t>(z),
             static_cast<int32_t>(w) );

    reinterpret_cast<PFNGLRASTERPOS4SPROC>(OpenGL::g_cached_gl_raster_pos_4s)(x,
                                                                              y,
                                                                              z,
                                                                              w);
}
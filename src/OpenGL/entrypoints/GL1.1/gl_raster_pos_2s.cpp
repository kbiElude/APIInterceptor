/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_2s.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos2s(GLshort x,
                                       GLshort y)
{
    AI_TRACE("glRasterPos2s(x=[%d] y=[%d])",
             static_cast<int32_t>(x),
             static_cast<int32_t>(y) );

    reinterpret_cast<PFNGLRASTERPOS2SPROC>(OpenGL::g_cached_gl_raster_pos_2s)(x,
                                                                              y);
}
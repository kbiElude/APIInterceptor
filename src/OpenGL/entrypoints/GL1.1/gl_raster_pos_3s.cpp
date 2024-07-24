/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_3s.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos3s(GLshort x,
                                       GLshort y,
                                       GLshort z)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glRasterPos3d(x=[%.4lf], y=[%.4lf], z=[%.4lf])",
             static_cast<int32_t>(x),
             static_cast<int32_t>(y),
             static_cast<int32_t>(z) );

    reinterpret_cast<PFNGLRASTERPOS3SPROC>(OpenGL::g_cached_gl_raster_pos_3s)(x,
                                                                              y,
                                                                              z);
}
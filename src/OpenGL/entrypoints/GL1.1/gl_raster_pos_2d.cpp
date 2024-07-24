/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_2d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos2d(GLdouble x,
                                       GLdouble y)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glRasterPos2d(x=[%.4lf] y=[%.4lf])",
             x,
             y);

    reinterpret_cast<PFNGLRASTERPOS2DPROC>(OpenGL::g_cached_gl_raster_pos_2d)(x,
                                                                              y);
}
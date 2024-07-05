/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_4d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos4d(GLdouble x,
                                       GLdouble y,
                                       GLdouble z,
                                       GLdouble w)
{
    AI_TRACE("glRasterPos4d(x=[%.4lf], y=[%.4lf], z=[%.4lf], w=[%.4lf])",
             x,
             y,
             z,
             w);

    reinterpret_cast<PFNGLRASTERPOS4DPROC>(OpenGL::g_cached_gl_raster_pos_4d)(x,
                                                                              y,
                                                                              z,
                                                                              w);
}
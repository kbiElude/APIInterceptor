/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_3d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos3d(GLdouble x,
                                       GLdouble y,
                                       GLdouble z)
{
    AI_TRACE("glRasterPos3d(x=[%.4lf], y=[%.4lf], z=[%.4lf])",
             x,
             y,
             z);

    reinterpret_cast<PFNGLRASTERPOS3DPROC>(OpenGL::g_cached_gl_raster_pos_3d)(x,
                                                                              y,
                                                                              z);
}
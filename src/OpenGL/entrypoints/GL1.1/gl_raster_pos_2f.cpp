/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_2f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos2f(GLfloat x,
                                       GLfloat y)
{
    AI_TRACE("glRasterPos2f(x=[%.4f] y=[%.4f])",
             x,
             y);

    reinterpret_cast<PFNGLRASTERPOS2FPROC>(OpenGL::g_cached_gl_raster_pos_2f)(x,
                                                                              y);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_4f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos4f(GLfloat x,
                                       GLfloat y,
                                       GLfloat z,
                                       GLfloat w)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glRasterPos4f(x=[%.4lf], y=[%.4lf], z=[%.4lf], w=[%.4lf])",
             x,
             y,
             z,
             w);

    reinterpret_cast<PFNGLRASTERPOS4FPROC>(OpenGL::g_cached_gl_raster_pos_4f)(x,
                                                                              y,
                                                                              z,
                                                                              w);
}
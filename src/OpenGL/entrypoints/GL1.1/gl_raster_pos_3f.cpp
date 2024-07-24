/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_3f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos3f(GLfloat x,
                                       GLfloat y,
                                       GLfloat z)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glRasterPos3f(x=[%.4f], y=[%.4f], z=[%.4f])",
             x,
             y,
             z);

    reinterpret_cast<PFNGLRASTERPOS3FPROC>(OpenGL::g_cached_gl_raster_pos_3f)(x,
                                                                              y,
                                                                              z);
}
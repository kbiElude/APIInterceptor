/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_2dv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos2dv(const GLdouble* v)
{
    AI_TRACE("glRasterPos2dv(v=[%p])",
             v);

    reinterpret_cast<PFNGLRASTERPOS2DVPROC>(OpenGL::g_cached_gl_raster_pos_2dv)(v);
}
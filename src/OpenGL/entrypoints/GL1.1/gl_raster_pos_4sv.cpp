/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_4sv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos4sv(const GLshort* v)
{
    AI_TRACE("glRasterPos4sv(v=[%p])",
             v);

    reinterpret_cast<PFNGLRASTERPOS4SVPROC>(OpenGL::g_cached_gl_raster_pos_4sv)(v);
}
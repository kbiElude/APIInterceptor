/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_4iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos4iv(const GLint* v)
{
    AI_TRACE("glRasterPos4iv(v=[%p])",
             v);

    reinterpret_cast<PFNGLRASTERPOS4IVPROC>(OpenGL::g_cached_gl_raster_pos_4iv)(v);
}
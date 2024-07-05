/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_2fv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos2fv(const GLfloat* v)
{
    AI_TRACE("glRasterPos2fv(v=[%p])",
             v);

    reinterpret_cast<PFNGLRASTERPOS2FVPROC>(OpenGL::g_cached_gl_raster_pos_2fv)(v);
}
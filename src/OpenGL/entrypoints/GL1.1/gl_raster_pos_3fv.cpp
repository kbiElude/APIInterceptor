/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_3fv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos3fv(const GLfloat* v)
{
    AI_TRACE("glRasterPos3fv(v=[%p])",
             v);

    reinterpret_cast<PFNGLRASTERPOS3FVPROC>(OpenGL::g_cached_gl_raster_pos_3fv)(v);
}
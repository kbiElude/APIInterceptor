/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_4fv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos4fv(const GLfloat* v)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glRasterPos4fv(v=[%p])",
             v);

    reinterpret_cast<PFNGLRASTERPOS4FVPROC>(OpenGL::g_cached_gl_raster_pos_4fv)(v);
}
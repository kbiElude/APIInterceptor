/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_2iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos2iv(const GLint* v)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glRasterPos2iv(v=[%p])",
             v);

    reinterpret_cast<PFNGLRASTERPOS2IVPROC>(OpenGL::g_cached_gl_raster_pos_2iv)(v);
}
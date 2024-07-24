/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_2i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRasterPos2i(GLint x,
                                       GLint y)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glRasterPos2i(x=[%d] y=[%d])",
             x,
             y);

    reinterpret_cast<PFNGLRASTERPOS2IPROC>(OpenGL::g_cached_gl_raster_pos_2i)(x,
                                                                              y);
}
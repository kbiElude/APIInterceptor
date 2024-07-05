/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_get_polygon_stipple.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetPolygonStipple(GLubyte* mask)
{
    AI_TRACE("glGetPolygonStipple(mask=[%p])",
             mask);

    reinterpret_cast<PFNGLGETPOLYGONSTIPPLEPROC>(OpenGL::g_cached_gl_get_polygon_stipple)(mask);
}
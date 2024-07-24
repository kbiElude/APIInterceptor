/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_map_grid_1d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMapGrid1d(GLint    un,
                                     GLdouble u1,
                                     GLdouble u2)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glMapGrid1d(un=[%d], u1=[%.4lf], u2=[%.4lf])",
             un,
             u1,
             u2);

    reinterpret_cast<PFNGLMAPGRID1DPROC>(OpenGL::g_cached_gl_map_grid_1d)(un,
                                                                          u1,
                                                                          u2);
}
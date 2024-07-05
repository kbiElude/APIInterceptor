/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_map_grid_2d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMapGrid2d(GLint    un,
                                     GLdouble u1,
                                     GLdouble u2,
                                     GLint    vn,
                                     GLdouble v1,
                                     GLdouble v2)
{
    AI_TRACE("glMapGrid2d(un=[%d], u1=[%.4lf], u2=[%.4lf], vn=[%d], v1=[%.4lf], v2=[%.4lf])",
             un,
             u1,
             u2,
             vn,
             v1,
             v2);

    reinterpret_cast<PFNGLMAPGRID2DPROC>(OpenGL::g_cached_gl_map_grid_2d)(un,
                                                                          u1,
                                                                          u2,
                                                                          vn,
                                                                          v1,
                                                                          v2);
}
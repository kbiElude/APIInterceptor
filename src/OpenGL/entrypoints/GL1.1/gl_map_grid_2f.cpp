/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_map_grid_2f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMapGrid2f(GLint   un,
                                     GLfloat u1,
                                     GLfloat u2,
                                     GLint   vn,
                                     GLfloat v1,
                                     GLfloat v2)
{
    AI_TRACE("glMapGrid2f(un=[%d], u1=[%.4f], u2=[%.4f], vn=[%d], v1=[%.4f], v2=[%.4f])",
             un,
             u1,
             u2,
             vn,
             v1,
             v2);

    reinterpret_cast<PFNGLMAPGRID2FPROC>(OpenGL::g_cached_gl_map_grid_2f)(un,
                                                                          u1,
                                                                          u2,
                                                                          vn,
                                                                          v1,
                                                                          v2);
}
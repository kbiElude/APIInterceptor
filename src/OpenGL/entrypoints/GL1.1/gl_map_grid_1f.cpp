/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_map_grid_1f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMapGrid1f(GLint   un,
                                     GLfloat u1,
                                     GLfloat u2)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glMapGrid1f(un=[%d], u1=[%.4f], u2=[%.4f])",
             un,
             u1,
             u2);

    reinterpret_cast<PFNGLMAPGRID1FPROC>(OpenGL::g_cached_gl_map_grid_1f)(un,
                                                                          u1,
                                                                          u2);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_color_maski.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColorMaski(GLuint    index,
                                      GLboolean r,
                                      GLboolean g,
                                      GLboolean b,
                                      GLboolean a)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glColorMaski(index=[%d] r=[%d] g=[%d] b=[%d] a=[%d])",
             index,
             (r == GL_TRUE) ? 1 : 0,
             (g == GL_TRUE) ? 1 : 0,
             (b == GL_TRUE) ? 1 : 0,
             (a == GL_TRUE) ? 1 : 0);

    reinterpret_cast<PFNGLCOLORMASKIPROC>(OpenGL::g_cached_gl_color_maski)(index,
                                                                           r,
                                                                           g,
                                                                           b,
                                                                           a);
}
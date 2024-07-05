/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_vertex_4i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex4i(GLint x,
                                    GLint y,
                                    GLint z,
                                    GLint w)
{
    AI_TRACE("glVertex4i(x=[%d], y=[%d], z=[%d], w=[%d])",
             x,
             y,
             z,
             w);

    reinterpret_cast<PFNGLVERTEX4IPROC>(OpenGL::g_cached_gl_vertex_4i)(x,
                                                                       y,
                                                                       z,
                                                                       w);
}
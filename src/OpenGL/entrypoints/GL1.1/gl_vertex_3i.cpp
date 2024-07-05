/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_vertex_3i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex3i(GLint x,
                                    GLint y,
                                    GLint z)
{
    AI_TRACE("glVertex3i(x=[%d], y=[%d], z=[%d])",
             x,
             y,
             z);

    reinterpret_cast<PFNGLVERTEX3IPROC>(OpenGL::g_cached_gl_vertex_3i)(x,
                                                                       y,
                                                                       z);
}
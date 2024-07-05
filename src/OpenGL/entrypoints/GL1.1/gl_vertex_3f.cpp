/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_vertex_3f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex3f(GLfloat x,
                                    GLfloat y,
                                    GLfloat z)
{
    AI_TRACE("glVertex3f(x=[%.4f], y=[%.4f], z=[%.4f])",
             x,
             y,
             z);

    reinterpret_cast<PFNGLVERTEX3FPROC>(OpenGL::g_cached_gl_vertex_3f)(x,
                                                                       y,
                                                                       z);
}
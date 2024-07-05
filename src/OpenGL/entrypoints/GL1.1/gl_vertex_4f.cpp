/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_vertex_4f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex4f(GLfloat x,
                                    GLfloat y,
                                    GLfloat z,
                                    GLfloat w)
{
    AI_TRACE("glVertex4f(x=[%.4f], y=[%.4f], z=[%.4f], w=[%.4f])",
             x,
             y,
             z,
             w);

    reinterpret_cast<PFNGLVERTEX4FPROC>(OpenGL::g_cached_gl_vertex_4f)(x,
                                                                       y,
                                                                       z,
                                                                       w);
}
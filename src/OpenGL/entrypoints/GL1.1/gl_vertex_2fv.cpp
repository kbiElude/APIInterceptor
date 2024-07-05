/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_vertex_2fv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex2fv(const GLfloat* v)
{
    AI_TRACE("glVertex2fv(v.x=[%.4f], v.y=[%.4f])",
             v[0],
             v[1]);

    reinterpret_cast<PFNGLVERTEX2FVPROC>(OpenGL::g_cached_gl_vertex_2fv)(v);
}
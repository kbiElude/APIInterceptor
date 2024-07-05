/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_vertex_3fv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex3fv(const GLfloat* v)
{
    AI_TRACE("glVertex3fv(v.x=[%.4f], v.y=[%.4f], v.z=[%.4f], v.w=[%.4f])",
             v[0],
             v[1],
             v[2],
             v[3]);

    reinterpret_cast<PFNGLVERTEX3FVPROC>(OpenGL::g_cached_gl_vertex_3fv)(v);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_normal_3fv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiNormal3fv(const GLfloat* v)
{
    AI_TRACE("glNormal3fv(v=[%p])",
             v);

    reinterpret_cast<PFNGLNORMAL3FVPROC>(OpenGL::g_cached_gl_normal_3fv)(v);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_normal_3iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiNormal3iv(const GLint* v)
{
    AI_TRACE("glNormal3iv(v=[%p])",
             v);

    reinterpret_cast<PFNGLNORMAL3IVPROC>(OpenGL::g_cached_gl_normal_3iv)(v);
}
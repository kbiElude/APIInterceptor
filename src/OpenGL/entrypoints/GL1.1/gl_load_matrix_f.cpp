/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_load_matrix_f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiLoadMatrixf(const GLfloat* m)
{
    AI_TRACE("glLoadMatrixf(m=[%p])",
             m);

    reinterpret_cast<PFNGLLOADMATRIXFPROC>(OpenGL::g_cached_gl_load_matrix_f)(m);
}
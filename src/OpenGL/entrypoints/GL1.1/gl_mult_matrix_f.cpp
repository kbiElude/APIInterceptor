/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_mult_matrix_f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMultMatrixf(const GLfloat* m)
{
    AI_TRACE("glMultMatrixf(m=[%p])",
             m);

    reinterpret_cast<PFNGLMULTMATRIXFPROC>(OpenGL::g_cached_gl_mult_matrix_f)(m);
}
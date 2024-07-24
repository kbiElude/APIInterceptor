/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_load_matrix_d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiLoadMatrixd(const GLdouble* m)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glLoadMatrixd(m=[%p])",
             m);

    reinterpret_cast<PFNGLLOADMATRIXDPROC>(OpenGL::g_cached_gl_load_matrix_d)(m);
}
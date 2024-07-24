/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_mult_matrix_d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMultMatrixd(const GLdouble* m)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glMultMatrixd(m=[%p])",
             m);

    reinterpret_cast<PFNGLMULTMATRIXDPROC>(OpenGL::g_cached_gl_mult_matrix_d)(m);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL2.1/gl_uniform_matrix_3x2_fv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniformMatrix3x2fv(GLint          location,
                                              GLsizei        count,
                                              GLboolean      transpose,
                                              const GLfloat* value)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    /* TODO: Make me more useful */
    AI_TRACE("glUniformMatrix3x2fv(location=[%d] count=[%d] transpose=[%d] value=[%p])",
             location,
             static_cast<int32_t>(count),
             (transpose == GL_TRUE) ? 1 : 0,
             value);

    reinterpret_cast<PFNGLUNIFORMMATRIX3X2FVPROC>(OpenGL::g_cached_gl_uniform_matrix_3x2_fv)(location,
                                                                                             count,
                                                                                             transpose,
                                                                                             value);
}
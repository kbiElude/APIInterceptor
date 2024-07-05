/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_uniform_matrix_3fv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniformMatrix3fv(GLint          location,
                                            GLsizei        count,
                                            GLboolean      transpose,
                                            const GLfloat* value)
{
    /* TODO: Make me more useful */
    AI_TRACE("glUniformMatrix3fv(location=[%d] count=[%d] transpose=[%d] value=[%p])",
             location,
             static_cast<int32_t>(count),
             (transpose == GL_TRUE) ? 1 : 0,
             value);

    if (OpenGL::g_cached_gl_uniform_matrix_3fv == nullptr)
    {
        OpenGL::g_cached_gl_uniform_matrix_3fv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glUniformMatrix3fv");
    }

    reinterpret_cast<PFNGLUNIFORMMATRIX3FVPROC>(OpenGL::g_cached_gl_uniform_matrix_3fv)(location,
                                                                                        count,
                                                                                        transpose,
                                                                                        value);
}
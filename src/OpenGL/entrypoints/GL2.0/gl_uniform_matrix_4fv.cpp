/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_uniform_matrix_4fv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniformMatrix4fv(GLint          location,
                                            GLsizei        count,
                                            GLboolean      transpose,
                                            const GLfloat* value)
{
    /* TODO: Make me more useful */
    AI_TRACE("glUniformMatrix4fv(location=[%d] count=[%d] transpose=[%d] value=[%p])",
             location,
             static_cast<int32_t>(count),
             (transpose == GL_TRUE) ? 1 : 0,
             value);

    if (OpenGL::g_cached_gl_uniform_matrix_4fv == nullptr)
    {
        OpenGL::g_cached_gl_uniform_matrix_4fv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glUniformMatrix4fv");
    }

    reinterpret_cast<PFNGLUNIFORMMATRIX4FVPROC>(OpenGL::g_cached_gl_uniform_matrix_4fv)(location,
                                                                                        count,
                                                                                        transpose,
                                                                                        value);
}
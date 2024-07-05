/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_uniform_4f.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniform4f(GLint   location,
                                     GLfloat v0,
                                     GLfloat v1,
                                     GLfloat v2,
                                     GLfloat v3)
{
    AI_TRACE("glUniform4f(location=[%d] v0=[%.4f] v1=[%.4f] v2=[%.4f] v3=[%.4f])",
             location,
             v0,
             v1,
             v2,
             v3);

    if (OpenGL::g_cached_gl_uniform_4f == nullptr)
    {
        OpenGL::g_cached_gl_uniform_4f = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glUniform4f");
    }

    reinterpret_cast<PFNGLUNIFORM4FPROC>(OpenGL::g_cached_gl_uniform_4f)(location,
                                                                         v0,
                                                                         v1,
                                                                         v2,
                                                                         v3);
}
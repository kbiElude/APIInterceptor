/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_uniform_2f.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniform2f(GLint   location,
                                     GLfloat v0,
                                     GLfloat v1)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glUniform2f(location=[%d] v0=[%.4f] v1=[%.4f])",
             location,
             v0,
             v1);

    if (OpenGL::g_cached_gl_uniform_2f == nullptr)
    {
        OpenGL::g_cached_gl_uniform_2f = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glUniform2f");
    }

    reinterpret_cast<PFNGLUNIFORM2FPROC>(OpenGL::g_cached_gl_uniform_2f)(location,
                                                                         v0,
                                                                         v1);
}
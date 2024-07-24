/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_uniform_1f.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniform1f(GLint   location,
                                     GLfloat v0)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glUniform1f(location=[%d] v0=[%.4f])",
             location,
             v0);

    if (OpenGL::g_cached_gl_uniform_1f == nullptr)
    {
        OpenGL::g_cached_gl_uniform_1f = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glUniform1f");
    }

    reinterpret_cast<PFNGLUNIFORM1FPROC>(OpenGL::g_cached_gl_uniform_1f)(location,
                                                                         v0);
}
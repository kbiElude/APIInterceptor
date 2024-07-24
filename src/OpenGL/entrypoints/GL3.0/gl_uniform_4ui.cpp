/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_uniform_4ui.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniform4ui(GLint  location,
                                      GLuint v0,
                                      GLuint v1,
                                      GLuint v2,
                                      GLuint v3)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glUniform4ui(location=[%d] v0=[%u] v1=[%u] v2=[%u] v3=[%u])",
             location,
             v0,
             v1,
             v2,
             v3);

    if (OpenGL::g_cached_gl_uniform_4ui == nullptr)
    {
        OpenGL::g_cached_gl_uniform_4ui = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glUniform4ui");
    }

    reinterpret_cast<PFNGLUNIFORM4UIPROC>(OpenGL::g_cached_gl_uniform_4ui)(location,
                                                                           v0,
                                                                           v1,
                                                                           v2,
                                                                           v3);
}
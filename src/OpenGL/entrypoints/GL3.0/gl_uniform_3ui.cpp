/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_uniform_3ui.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniform3ui(GLint  location,
                                      GLuint v0,
                                      GLuint v1,
                                      GLuint v2)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glUniform3ui(location=[%d] v0=[%u] v1=[%u] v2=[%u])",
             location,
             v0,
             v1,
             v2);

    if (OpenGL::g_cached_gl_uniform_3ui == nullptr)
    {
        OpenGL::g_cached_gl_uniform_3ui = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glUniform3ui");
    }

    reinterpret_cast<PFNGLUNIFORM3UIPROC>(OpenGL::g_cached_gl_uniform_3ui)(location,
                                                                           v0,
                                                                           v1,
                                                                           v2);
}
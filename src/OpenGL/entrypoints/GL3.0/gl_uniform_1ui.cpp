/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_uniform_1ui.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniform1ui(GLint  location,
                                      GLuint v0)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glUniform1ui(location=[%d] v0=[%u])",
             location,
             v0);

    reinterpret_cast<PFNGLUNIFORM1UIPROC>(OpenGL::g_cached_gl_uniform_1ui)(location,
                                                                           v0);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_uniform_2ui.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniform2ui(GLint  location,
                                      GLuint v0,
                                      GLuint v1)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glUniform2ui(location=[%d] v0=[%u] v1=[%u])",
             location,
             v0,
             v1);

    reinterpret_cast<PFNGLUNIFORM2UIPROC>(OpenGL::g_cached_gl_uniform_2ui)(location,
                                                                           v0,
                                                                           v1);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_4i.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniform4i(GLint location,
                                     GLint v0,
                                     GLint v1,
                                     GLint v2,
                                     GLint v3)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glUniform4i(location=[%d] v0=[%d] v1=[%d] v2=[%d] v3=[%d])",
             location,
             v0,
             v1,
             v2,
             v3);

    reinterpret_cast<PFNGLUNIFORM4IPROC>(OpenGL::g_cached_gl_uniform_4i)(location,
                                                                         v0,
                                                                         v1,
                                                                         v2,
                                                                         v3);
}
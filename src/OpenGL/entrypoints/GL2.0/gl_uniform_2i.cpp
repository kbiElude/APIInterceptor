/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_uniform_2i.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniform2i(GLint location,
                                     GLint v0,
                                     GLint v1)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glUniform2i(location=[%d] v0=[%d] v1=[%d])",
             location,
             v0,
             v1);

    reinterpret_cast<PFNGLUNIFORM2IPROC>(OpenGL::g_cached_gl_uniform_2i)(location,
                                                                         v0,
                                                                         v1);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_uniform_3f.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniform3f(GLint   location,
                                     GLfloat v0,
                                     GLfloat v1,
                                     GLfloat v2)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glUniform3f(location=[%d] v0=[%.4f] v1=[%.4f] v2=[%.4f])",
             location,
             v0,
             v1,
             v2);

    reinterpret_cast<PFNGLUNIFORM3FPROC>(OpenGL::g_cached_gl_uniform_3f)(location,
                                                                         v0,
                                                                         v1,
                                                                         v2);
}
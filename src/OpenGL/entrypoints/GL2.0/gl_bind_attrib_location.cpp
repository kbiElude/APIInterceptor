/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_bind_attrib_location.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBindAttribLocation(GLuint  program,
                                              GLuint  index,
                                              GLchar* name)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glBindAttribLocation(program=[%d] index=[%d] name=[%s])",
             program,
             index,
             name);

    reinterpret_cast<PFNGLBINDATTRIBLOCATIONPROC>(OpenGL::g_cached_gl_bind_attrib_location)(program,
                                                                                            index,
                                                                                            name);
}
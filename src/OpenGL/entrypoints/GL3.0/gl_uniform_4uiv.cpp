/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_uniform_4uiv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniform4uiv(GLint         location,
                                       GLsizei       count,
                                       const GLuint* value)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    /* TODO: Make me more useful */
    AI_TRACE("glUniform4uiv(location=[%d] count=[%d] value=[%p])",
             location,
             static_cast<int32_t>(count),
             value);

    reinterpret_cast<PFNGLUNIFORM4UIVPROC>(OpenGL::g_cached_gl_uniform_4uiv)(location,
                                                                             count,
                                                                             value);
}
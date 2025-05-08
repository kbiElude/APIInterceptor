/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_3iv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniform3iv(GLint        location,
                                      GLsizei      count,
                                      const GLint* value)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    /* TODO: Make me more useful */
    AI_TRACE("glUniform3iv(location=[%d] count=[%d] value=[%p])",
             location,
             static_cast<int32_t>(count),
             value);

    reinterpret_cast<PFNGLUNIFORM3IVPROC>(OpenGL::g_cached_gl_uniform_3iv)(location,
                                                                           count,
                                                                           value);
}
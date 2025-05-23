/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL2.0/gl_shader_source.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiShaderSource(GLuint               shader,
                                        GLsizei              count,
                                        const GLchar* const* string,
                                        const GLint*         length)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    /* TODO: Make me more useful */
    AI_TRACE("glShaderSource(shader=[%u] count=[%d] string=[%p] length=[%p])",
             shader,
             static_cast<int32_t>(count),
             string,
             length);

    reinterpret_cast<PFNGLSHADERSOURCEPROC>(g_cached_gl_shader_source)(shader,
                                                                       count,
                                                                       string,
                                                                       length);
}
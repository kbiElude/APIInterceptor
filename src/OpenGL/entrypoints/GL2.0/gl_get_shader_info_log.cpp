/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_get_shader_info_log.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetShaderInfoLog(GLuint   shader,
                                            GLsizei  bufSize,
                                            GLsizei* length,
                                            GLchar*  infoLog)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetShaderInfoLog(shader=[%u] bufSize=[%d] length=[%p] infoLog=[%p])",
             shader,
             static_cast<int32_t>(bufSize),
             length,
             infoLog);

    reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>(OpenGL::g_cached_gl_get_shader_info_log)(shader,
                                                                                         bufSize,
                                                                                         length,
                                                                                         infoLog);
}
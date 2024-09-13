/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_get_program_info_log.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetProgramInfoLog(GLuint   program,
                                             GLsizei  bufSize,
                                             GLsizei* length,
                                             GLchar*  infoLog)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetProgramInfoLog(program=[%u] bufSize=[%d] length=[%p] infoLog=[%p])",
             program,
             static_cast<int32_t>(bufSize),
             length,
             infoLog);

    reinterpret_cast<PFNGLGETPROGRAMINFOLOGPROC>(OpenGL::g_cached_gl_get_program_info_log)(program,
                                                                                           bufSize,
                                                                                           length,
                                                                                           infoLog);
}
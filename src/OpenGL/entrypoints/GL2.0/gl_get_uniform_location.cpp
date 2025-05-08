/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_uniform_location.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLint AI_APIENTRY OpenGL::aiGetUniformLocation(GLuint        program,
                                               const GLchar* name)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetUniformLocation(program=[%u] name=[%s])",
             program,
             name);

    return reinterpret_cast<PFNGLGETUNIFORMLOCATIONPROC>(OpenGL::g_cached_gl_get_uniform_location)(program,
                                                                                                   name);
}
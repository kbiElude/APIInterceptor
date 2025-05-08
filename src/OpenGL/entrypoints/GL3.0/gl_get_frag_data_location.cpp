/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_frag_data_location.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLint AI_APIENTRY OpenGL::aiGetFragDataLocation(GLuint        program,
                                                const GLchar* name)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetFragDataLocation(program=[%u] name=[%s])",
             program,
             name);

    return reinterpret_cast<PFNGLGETFRAGDATALOCATIONPROC>(OpenGL::g_cached_gl_get_frag_data_location)(program,
                                                                                                      name);
}
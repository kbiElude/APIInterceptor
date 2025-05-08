/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL2.0/gl_create_shader.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

GLuint AI_APIENTRY OpenGL::aiCreateShader(GLenum type)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glCreateShader(type=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(type) );

    return reinterpret_cast<PFNGLCREATESHADERPROC>(OpenGL::g_cached_gl_create_shader)(type);
}
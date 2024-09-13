/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
  */
#include "OpenGL/entrypoints/GL2.0/gl_get_shaderiv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetShaderiv(GLuint shader,
                                       GLenum pname,
                                       GLint* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetShaderiv(shader=[%u] pname=[%s] params=[%p])",
             shader,
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    reinterpret_cast<PFNGLGETSHADERIVPROC>(OpenGL::g_cached_gl_get_shaderiv)(shader,
                                                                             pname,
                                                                             params);
}
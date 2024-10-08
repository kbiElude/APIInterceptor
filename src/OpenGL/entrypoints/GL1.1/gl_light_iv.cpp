/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_light_iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiLightiv(GLenum       light,
                                   GLenum       pname,
                                   const GLint* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glLightiv(light=[%s], pname=[%s], params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(light),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    reinterpret_cast<PFNGLLIGHTIVPROC>(OpenGL::g_cached_gl_light_iv)(light,
                                                                     pname,
                                                                     params);
}
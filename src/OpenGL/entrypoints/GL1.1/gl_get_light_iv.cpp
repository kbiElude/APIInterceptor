/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_get_light_iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetLightiv(GLenum light,
                                      GLenum pname,
                                      GLint* params)
{
    AI_TRACE("glGetLightiv(light=[%s], pname=[%s], params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(light),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    reinterpret_cast<PFNGLGETLIGHTIVPROC>(OpenGL::g_cached_gl_get_light_iv)(light,
                                                                            pname,
                                                                            params);
}
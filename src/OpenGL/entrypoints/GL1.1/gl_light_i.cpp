/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_light_i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiLighti(GLenum light,
                                  GLenum pname,
                                  GLint  param)
{
    AI_TRACE("glLighti(light=[%s], pname=[%s], param=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(light),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             param);

    reinterpret_cast<PFNGLLIGHTIPROC>(OpenGL::g_cached_gl_light_i)(light,
                                                                   pname,
                                                                   param);
}
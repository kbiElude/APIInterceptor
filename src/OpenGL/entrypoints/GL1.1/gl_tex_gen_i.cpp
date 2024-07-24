/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_gen_i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexGeni(GLenum coord,
                                   GLenum pname,
                                   GLint  param)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glTexGeni(coord=[%s], pname=[%s], param=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(coord),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             param);

    reinterpret_cast<PFNGLTEXGENIPROC>(OpenGL::g_cached_gl_tex_gen_i)(coord,
                                                                      pname,
                                                                      param);
}
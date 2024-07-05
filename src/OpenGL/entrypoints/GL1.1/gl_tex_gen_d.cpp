/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_gen_d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexGend(GLenum   coord,
                                   GLenum   pname,
                                   GLdouble param)
{
    AI_TRACE("glTexGend(coord=[%s], pname=[%s], param=[%.4lf])",
             OpenGL::Utils::get_raw_string_for_gl_enum(coord),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             param);

    reinterpret_cast<PFNGLTEXGENDPROC>(OpenGL::g_cached_gl_tex_gen_d)(coord,
                                                                      pname,
                                                                      param);
}
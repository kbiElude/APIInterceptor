/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_material_i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMateriali(GLenum face,
                                     GLenum pname,
                                     GLint  param)
{
    AI_TRACE("glMateriali(face=[%s], pname=[%s], param=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(face),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             param);

    reinterpret_cast<PFNGLMATERIALIPROC>(OpenGL::g_cached_gl_material_i)(face,
                                                                         pname,
                                                                         param);
}
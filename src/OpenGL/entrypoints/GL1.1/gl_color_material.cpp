/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_material.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColorMaterial(GLenum face,
                                         GLenum mode)
{
    AI_TRACE("glColorMaterial(face=[%s], mode=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(face),
             OpenGL::Utils::get_raw_string_for_gl_enum(mode) );

    reinterpret_cast<PFNGLCOLORMATERIALPROC>(OpenGL::g_cached_gl_color_material)(face,
                                                                                 mode);
}
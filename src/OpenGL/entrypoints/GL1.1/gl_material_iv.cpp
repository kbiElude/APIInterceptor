/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_material_iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMaterialiv(GLenum       face,
                                      GLenum       pname,
                                      const GLint* params)
{
    AI_TRACE("glMaterialiv(face=[%s], pname=[%s], params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(face),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    reinterpret_cast<PFNGLMATERIALIVPROC>(OpenGL::g_cached_gl_material_iv)(face,
                                                                           pname,
                                                                           params);
}
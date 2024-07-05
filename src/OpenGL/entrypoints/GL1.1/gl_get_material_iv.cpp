/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_get_material_iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetMaterialiv(GLenum face,
                                         GLenum pname,
                                         GLint* params)
{
    AI_TRACE("glGetMaterialiv(face=[%s], pname=[%s], params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(face),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    reinterpret_cast<PFNGLGETMATERIALIVPROC>(OpenGL::g_cached_gl_get_material_iv)(face,
                                                                                  pname,
                                                                                  params);
}
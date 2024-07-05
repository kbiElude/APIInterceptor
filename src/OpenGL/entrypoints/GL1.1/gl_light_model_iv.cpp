/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_light_model_iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiLightModeliv(GLenum       pname,
                                        const GLint* params)
{
    AI_TRACE("glLightModeliv(pname=[%s], params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    reinterpret_cast<PFNGLLIGHTMODELIVPROC>(OpenGL::g_cached_gl_light_model_iv)(pname,
                                                                                params);
}
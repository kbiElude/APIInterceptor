/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_fogiv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFogiv(GLenum       pname,
                                 const GLint* params)
{
    AI_TRACE("glFogiv(pname=[%s], params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    reinterpret_cast<PFNGLFOGIVPROC>(OpenGL::g_cached_gl_fogiv)(pname,
                                                                params);
}
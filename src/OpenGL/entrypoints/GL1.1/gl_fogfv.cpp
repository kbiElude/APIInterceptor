/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_fogfv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFogfv(GLenum         pname,
                                 const GLfloat* params)
{
    AI_TRACE("glFogfv(pname=[%s], params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    reinterpret_cast<PFNGLFOGFVPROC>(OpenGL::g_cached_gl_fogfv)(pname,
                                                                params);
}
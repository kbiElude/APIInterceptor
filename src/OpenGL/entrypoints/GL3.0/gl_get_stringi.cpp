/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_get_stringi.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

const GLubyte *APIENTRY OpenGL::aiGetStringi(GLenum name,
                                             GLuint index)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetStringi(name=[%s] index=[%u])",
             OpenGL::Utils::get_raw_string_for_gl_enum(name),
             index);

    return reinterpret_cast<PFNGLGETSTRINGIPROC>(OpenGL::g_cached_gl_get_stringi)(name,
                                                                                  index);
}
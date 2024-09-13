/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_get_string.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

const GLubyte* APIENTRY OpenGL::aiGetString(GLenum name)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetString(name=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(name) );

    return reinterpret_cast<PFNGLGETSTRINGPROC>(OpenGL::g_cached_gl_get_string)(name);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_get_integerv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetIntegerv(GLenum pname,
                                       GLint* data)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetIntegerv(pname=[%s] data=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             data);

    reinterpret_cast<PFNGLGETINTEGERVPROC>(OpenGL::g_cached_gl_get_integerv)(pname,
                                                                             data);
}
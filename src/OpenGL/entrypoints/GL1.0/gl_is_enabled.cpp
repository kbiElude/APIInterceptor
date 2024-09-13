/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_is_enabled.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsEnabled(GLenum cap)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glIsEnabled(cap=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(cap) );

    return reinterpret_cast<PFNGLISENABLEDPROC>(OpenGL::g_cached_gl_is_enabled)(cap);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_is_enabledi.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsEnabledi(GLenum target,
                                               GLuint index)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glIsEnabledi(target=[%s] index=[%u])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             index);

    return reinterpret_cast<PFNGLISENABLEDIPROC>(OpenGL::g_cached_gl_is_enabledi)(target,
                                                                                  index);
}
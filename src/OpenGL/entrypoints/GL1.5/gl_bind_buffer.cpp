/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.5/gl_bind_buffer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBindBuffer(GLenum target,
                                      GLuint buffer)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glBindBuffer(target=[%s] buffer=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             buffer);

    reinterpret_cast<PFNGLBINDBUFFERPROC>(OpenGL::g_cached_gl_bind_buffer)(target,
                                                                           buffer);
}
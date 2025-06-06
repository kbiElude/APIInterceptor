/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_disablei.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDisablei(GLenum target,
                                    GLuint index)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glDisablei(target=[%s] index=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             index);

    reinterpret_cast<PFNGLDISABLEIPROC>(OpenGL::g_cached_gl_disablei)(target,
                                                                      index);
}
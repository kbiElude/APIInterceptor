/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_check_framebuffer_status.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

GLenum AI_APIENTRY OpenGL::aiCheckFramebufferStatus(GLenum target)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glCheckFramebufferStatus(target=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target) );

    return reinterpret_cast<PFNGLCHECKFRAMEBUFFERSTATUSPROC>(OpenGL::g_cached_gl_check_framebuffer_status)(target);
}
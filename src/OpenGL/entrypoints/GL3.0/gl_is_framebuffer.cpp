/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_is_framebuffer.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsFramebuffer(GLuint framebuffer)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glIsFramebuffer(framebuffer=[%u])",
             framebuffer);

    return reinterpret_cast<PFNGLISFRAMEBUFFERPROC>(OpenGL::g_cached_gl_is_framebuffer)(framebuffer);
}
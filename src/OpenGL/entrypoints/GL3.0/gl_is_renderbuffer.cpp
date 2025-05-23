/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_is_renderbuffer.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsRenderbuffer(GLuint renderbuffer)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glIsRenderbuffer(renderbuffer=[%u])",
             renderbuffer);

    return reinterpret_cast<PFNGLISRENDERBUFFERPROC>(OpenGL::g_cached_gl_is_renderbuffer)(renderbuffer);
}
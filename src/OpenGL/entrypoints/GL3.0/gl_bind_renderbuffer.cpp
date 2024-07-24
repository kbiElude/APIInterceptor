/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_bind_renderbuffer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBindRenderbuffer(GLenum target,
                                            GLuint renderbuffer)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glBindRenderbuffer(target=[%s] renderbuffer=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             renderbuffer);

    if (OpenGL::g_cached_gl_bind_renderbuffer == nullptr)
    {
        OpenGL::g_cached_gl_bind_renderbuffer = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glBindRenderbuffer");
    }

    reinterpret_cast<PFNGLBINDRENDERBUFFERPROC>(OpenGL::g_cached_gl_bind_renderbuffer)(target,
                                                                                       renderbuffer);
}
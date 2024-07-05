/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_is_renderbuffer.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsRenderbuffer(GLuint renderbuffer)
{
    AI_TRACE("glIsRenderbuffer(renderbuffer=[%u])",
             renderbuffer);

    if (OpenGL::g_cached_gl_is_renderbuffer == nullptr)
    {
        OpenGL::g_cached_gl_is_renderbuffer = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glIsRenderbuffer");
    }

    return reinterpret_cast<PFNGLISRENDERBUFFERPROC>(OpenGL::g_cached_gl_is_renderbuffer)(renderbuffer);
}
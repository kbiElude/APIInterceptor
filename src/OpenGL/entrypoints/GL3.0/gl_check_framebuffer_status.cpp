/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_check_framebuffer_status.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

GLenum AI_APIENTRY OpenGL::aiCheckFramebufferStatus(GLenum target)
{
    AI_TRACE("glCheckFramebufferStatus(target=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target) );

    if (OpenGL::g_cached_gl_check_framebuffer_status == nullptr)
    {
        OpenGL::g_cached_gl_check_framebuffer_status = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glCheckFramebufferStatus");
    }

    return reinterpret_cast<PFNGLCHECKFRAMEBUFFERSTATUSPROC>(OpenGL::g_cached_gl_check_framebuffer_status)(target);
}
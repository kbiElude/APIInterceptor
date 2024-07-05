/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_get_framebuffer_attachment_parameteriv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetFramebufferAttachmentParameteriv(GLenum target,
                                                               GLenum attachment,
                                                               GLenum pname,
                                                               GLint* params)
{
    AI_TRACE("glGetFramebufferAttachmentParameteriv(target=[%s] attachment=[%s] pname=[%s] params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(attachment),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_get_framebuffer_attachment_parameteriv == nullptr)
    {
        OpenGL::g_cached_gl_get_framebuffer_attachment_parameteriv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetFramebufferAttachmentParameteriv");
    }

    reinterpret_cast<PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC>(OpenGL::g_cached_gl_get_framebuffer_attachment_parameteriv)(target,
                                                                                                                               attachment,
                                                                                                                               pname,
                                                                                                                               params);
}
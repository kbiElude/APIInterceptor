/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_blit_framebuffer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBlitFramebuffer(GLint      srcX0,
                                           GLint      srcY0,
                                           GLint      srcX1,
                                           GLint      srcY1,
                                           GLint      dstX0,
                                           GLint      dstY0,
                                           GLint      dstX1,
                                           GLint      dstY1,
                                           GLbitfield mask,
                                           GLenum     filter)
{
    AI_TRACE("glBlitFramebuffer(srcX0=[%d] srcY0=[%d] srcX1=[%d] srcY1=[%d] dstX0=[%d] dstY0=[%d] dstX1=[%d] dstY1=[%d] mask=[%s] filter=[%s]",
             srcX0,
             srcY0,
             srcX1,
             srcY1,
             dstX0,
             dstY0,
             dstX1,
             dstY1,
             OpenGL::Utils::get_raw_string_for_gl_bitfield(BitfieldType::Blit_Mask, mask),
             OpenGL::Utils::get_raw_string_for_gl_enum    (filter) );

    if (OpenGL::g_cached_gl_blit_framebuffer == nullptr)
    {
        OpenGL::g_cached_gl_blit_framebuffer = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glBlitFramebuffer");
    }

    reinterpret_cast<PFNGLBLITFRAMEBUFFERPROC>(OpenGL::g_cached_gl_blit_framebuffer)(srcX0,
                                                                                     srcY0,
                                                                                     srcX1,
                                                                                     srcY1,
                                                                                     dstX0,
                                                                                     dstY0,
                                                                                     dstX1,
                                                                                     dstY1,
                                                                                     mask,
                                                                                     filter);
}
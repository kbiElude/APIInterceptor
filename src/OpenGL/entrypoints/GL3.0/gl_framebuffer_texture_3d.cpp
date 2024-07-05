/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_framebuffer_texture_3d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFramebufferTexture3D(GLenum target,
                                                GLenum attachment,
                                                GLenum textarget,
                                                GLuint texture,
                                                GLint  level,
                                                GLint  zoffset)
{
    AI_TRACE("glFramebufferTexture3D(target=[%s] attachment=[%s] textarget=[%s] texture=[%u] level=[%d] zoffset=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(attachment),
             OpenGL::Utils::get_raw_string_for_gl_enum(textarget),
             texture,
             level,
             zoffset);

    if (OpenGL::g_cached_gl_framebuffer_texture_3D == nullptr)
    {
        OpenGL::g_cached_gl_framebuffer_texture_3D = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glFramebufferTexture3D");
    }

    reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE3DPROC>(OpenGL::g_cached_gl_framebuffer_texture_3D)(target,
                                                                                                attachment,
                                                                                                textarget,
                                                                                                texture,
                                                                                                level,
                                                                                                zoffset);
}
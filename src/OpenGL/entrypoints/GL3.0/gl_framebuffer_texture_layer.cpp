/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_framebuffer_texture_layer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFramebufferTextureLayer(GLenum target,
                                                   GLenum attachment,
                                                   GLuint texture,
                                                   GLint  level,
                                                   GLint  layer)
{
    AI_TRACE("glFramebufferTextureLayer(target=[%s] attachment=[%s] texture=[%u] level=[%d] layer=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(attachment),
             texture,
             level,
             layer);

    if (OpenGL::g_cached_gl_framebuffer_texture_layer == nullptr)
    {
        OpenGL::g_cached_gl_framebuffer_texture_layer = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glFramebufferTextureLayer");
    }

    reinterpret_cast<PFNGLFRAMEBUFFERTEXTURELAYERPROC>(OpenGL::g_cached_gl_framebuffer_texture_layer)(target,
                                                                                                      attachment,
                                                                                                      texture,
                                                                                                      level,
                                                                                                      layer);
}
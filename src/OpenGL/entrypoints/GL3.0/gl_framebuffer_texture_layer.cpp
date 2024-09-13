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
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glFramebufferTextureLayer(target=[%s] attachment=[%s] texture=[%u] level=[%d] layer=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(attachment),
             texture,
             level,
             layer);

    reinterpret_cast<PFNGLFRAMEBUFFERTEXTURELAYERPROC>(OpenGL::g_cached_gl_framebuffer_texture_layer)(target,
                                                                                                      attachment,
                                                                                                      texture,
                                                                                                      level,
                                                                                                      layer);
}
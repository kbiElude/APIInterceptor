/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
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
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glFramebufferTexture3D(target=[%s] attachment=[%s] textarget=[%s] texture=[%u] level=[%d] zoffset=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(attachment),
             OpenGL::Utils::get_raw_string_for_gl_enum(textarget),
             texture,
             level,
             zoffset);


    reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE3DPROC>(OpenGL::g_cached_gl_framebuffer_texture_3D)(target,
                                                                                                attachment,
                                                                                                textarget,
                                                                                                texture,
                                                                                                level,
                                                                                                zoffset);
}
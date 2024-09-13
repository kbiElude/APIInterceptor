/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.2/gl_tex_sub_image_3d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexSubImage3D(GLenum      target,
                                         GLint       level,
                                         GLint       xoffset,
                                         GLint       yoffset,
                                         GLint       zoffset,
                                         GLsizei     width,
                                         GLsizei     height,
                                         GLsizei     depth,
                                         GLenum      format,
                                         GLenum      type,
                                         const void* pixels)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glTexSubImage3D(target=[%s] level=[%d] xoffset=[%d] yoffset=[%d] zoffset=[%d] width=[%d] height=[%d] depth=[%d] format=[%s] type=[%s] pixels=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             xoffset,
             yoffset,
             zoffset,
             static_cast<int32_t>(width),
             static_cast<int32_t>(height),
             static_cast<int32_t>(depth),
             OpenGL::Utils::get_raw_string_for_gl_enum(format),
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             pixels);

    reinterpret_cast<PFNGLTEXSUBIMAGE3DPROC>(OpenGL::g_cached_gl_tex_sub_image_3D)(target,
                                                                                   level,
                                                                                   xoffset,
                                                                                   yoffset,
                                                                                   zoffset,
                                                                                   width,
                                                                                   height,
                                                                                   depth,
                                                                                   format,
                                                                                   type,
                                                                                   pixels);
}
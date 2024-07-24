/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_sub_image_2d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexSubImage2D(GLenum      target,
                                         GLint       level,
                                         GLint       xoffset,
                                         GLint       yoffset,
                                         GLsizei     width,
                                         GLsizei     height,
                                         GLenum      format,
                                         GLenum      type,
                                         const void* pixels)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glTexSubImage2D(target=[%s] level=[%d] xoffset=[%d] yoffset=[%d] width=[%d] height=[%d] format=[%s] type=[%s] pixels=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             xoffset,
             yoffset,
             static_cast<int32_t>(width),
             static_cast<int32_t>(height),
             OpenGL::Utils::get_raw_string_for_gl_enum(format),
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             pixels);

    if (OpenGL::g_cached_gl_tex_sub_image_2D == nullptr)
    {
        OpenGL::g_cached_gl_tex_sub_image_2D = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glTexSubImage2D");
    }

    reinterpret_cast<PFNGLTEXSUBIMAGE2DPROC>(OpenGL::g_cached_gl_tex_sub_image_2D)(target,
                                                                                   level,
                                                                                   xoffset,
                                                                                   yoffset,
                                                                                   width,
                                                                                   height,
                                                                                   format,
                                                                                   type,
                                                                                   pixels);
}
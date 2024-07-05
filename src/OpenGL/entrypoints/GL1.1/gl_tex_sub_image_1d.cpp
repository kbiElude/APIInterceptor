/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_sub_image_1d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexSubImage1D(GLenum      target,
                                         GLint       level,
                                         GLint       xoffset,
                                         GLsizei     width,
                                         GLenum      format,
                                         GLenum      type,
                                         const void* pixels)
{
    AI_TRACE("glTexSubImage1D(target=[%s] level=[%d] xoffset=[%d] width=[%d] format=[%s] type=[%s] pixels=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             xoffset,
             static_cast<int32_t>(width),
             OpenGL::Utils::get_raw_string_for_gl_enum(format),
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             pixels);

    if (OpenGL::g_cached_gl_tex_sub_image_1D == nullptr)
    {
        OpenGL::g_cached_gl_tex_sub_image_1D = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glTexSubImage1D");
    }

    reinterpret_cast<PFNGLTEXSUBIMAGE1DPROC>(OpenGL::g_cached_gl_tex_sub_image_1D)(target,
                                                                                   level,
                                                                                   xoffset,
                                                                                   width,
                                                                                   format,
                                                                                   type,
                                                                                   pixels);
}
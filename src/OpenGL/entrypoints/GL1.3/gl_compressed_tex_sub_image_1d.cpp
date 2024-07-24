/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_sub_image_1d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCompressedTexSubImage1D(GLenum      target,
                                                   GLint       level,
                                                   GLint       xoffset,
                                                   GLsizei     width,
                                                   GLenum      format,
                                                   GLsizei     imageSize,
                                                   const void* data)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glCompressedTexSubImage1D(target=[%s] level=[%d] xoffset=[%d] width=[%d] format=[%s] imageSize=[%d] data=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             xoffset,
             static_cast<int32_t>(width),
             OpenGL::Utils::get_raw_string_for_gl_enum(format),
             static_cast<int32_t>(imageSize),
             data);

    if (OpenGL::g_cached_gl_compressed_tex_sub_image_1D == nullptr)
    {
        OpenGL::g_cached_gl_compressed_tex_sub_image_1D = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glCompressedTexSubImage1D");
    }

    reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC>(OpenGL::g_cached_gl_compressed_tex_sub_image_1D)(target,
                                                                                                        level,
                                                                                                        xoffset,
                                                                                                        width,
                                                                                                        format,
                                                                                                        imageSize,
                                                                                                        data);
}
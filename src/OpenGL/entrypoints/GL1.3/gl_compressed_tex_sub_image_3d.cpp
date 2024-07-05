/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_sub_image_3d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCompressedTexSubImage3D(GLenum      target,
                                                   GLint       level,
                                                   GLint       xoffset,
                                                   GLint       yoffset,
                                                   GLint       zoffset,
                                                   GLsizei     width,
                                                   GLsizei     height,
                                                   GLsizei     depth,
                                                   GLenum      format,
                                                   GLsizei     imageSize,
                                                   const void* data)
{
    AI_TRACE("glCompressedTexSubImage3D(target=[%s] level=[%d] xoffset=[%d] yoffset=[%d] zoffset=[%d] width=[%d] height=[%d] depth={%d] format=[%s] imageSize=[%d] data=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             xoffset,
             yoffset,
             zoffset,
             static_cast<int32_t>(width),
             static_cast<int32_t>(height),
             static_cast<int32_t>(depth),
             OpenGL::Utils::get_raw_string_for_gl_enum(format),
             static_cast<int32_t>(imageSize),
             data);

    if (OpenGL::g_cached_gl_compressed_tex_sub_image_3D == nullptr)
    {
        OpenGL::g_cached_gl_compressed_tex_sub_image_3D = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glCompressedTexSubImage3D");
    }

    reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC>(OpenGL::g_cached_gl_compressed_tex_sub_image_3D)(target,
                                                                                                        level,
                                                                                                        xoffset,
                                                                                                        yoffset,
                                                                                                        zoffset,
                                                                                                        width,
                                                                                                        height,
                                                                                                        depth,
                                                                                                        format,
                                                                                                        imageSize,
                                                                                                        data);
}
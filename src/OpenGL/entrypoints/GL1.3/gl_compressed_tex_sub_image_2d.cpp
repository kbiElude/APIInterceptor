/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_sub_image_2d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCompressedTexSubImage2D(GLenum      target,
                                                   GLint       level,
                                                   GLint       xoffset,
                                                   GLint       yoffset,
                                                   GLsizei     width,
                                                   GLsizei     height,
                                                   GLenum      format,
                                                   GLsizei     imageSize,
                                                   const void* data)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glCompressedTexSubImage2D(target=[%s] level=[%d] xoffset=[%d] yoffset=[%d] width=[%d] height=[%d] format=[%s] imageSize=[%d] data=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             xoffset,
             yoffset,
             static_cast<int32_t>(width),
             static_cast<int32_t>(height),
             OpenGL::Utils::get_raw_string_for_gl_enum(format),
             static_cast<int32_t>(imageSize),
             data);

    reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC>(OpenGL::g_cached_gl_compressed_tex_sub_image_2D)(target,
                                                                                                        level,
                                                                                                        xoffset,
                                                                                                        yoffset,
                                                                                                        width,
                                                                                                        height,
                                                                                                        format,
                                                                                                        imageSize,
                                                                                                        data);
}
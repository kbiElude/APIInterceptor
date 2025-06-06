/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_sub_image_3d.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
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
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

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
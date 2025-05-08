/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_image_1d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCompressedTexImage1D(GLenum      target,
                                                GLint       level,
                                                GLenum      internalformat,
                                                GLsizei     width,
                                                GLint       border,
                                                GLsizei     imageSize,
                                                const void* data)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glCompressedTexImage1D(target=[%s] level=[%d] internalformat=[%s] width=[%d] border=[%d] imageSize=[%d] data=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
             static_cast<int32_t>(width),
             border,
             imageSize,
             data);

    reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE1DPROC>(OpenGL::g_cached_gl_compressed_tex_image_1D)(target,
                                                                                                 level,
                                                                                                 internalformat,
                                                                                                 width,
                                                                                                 border,
                                                                                                 imageSize,
                                                                                                 data);
}
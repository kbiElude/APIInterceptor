/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_image_3d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCompressedTexImage3D(GLenum      target,
                                                GLint       level,
                                                GLenum      internalformat,
                                                GLsizei     width,
                                                GLsizei     height,
                                                GLsizei     depth,
                                                GLint       border,
                                                GLsizei     imageSize,
                                                const void* data)
{
    AI_TRACE("glCompressedTexImage3D(target=[%s] level=[%d] internalformat=[%s] width=[%d] height=[%d] depth=[%d] border=[%d] imageSize=[%d] data=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
             static_cast<int32_t>(width),
             static_cast<int32_t>(height),
             static_cast<int32_t>(depth),
             border,
             static_cast<int32_t>(imageSize),
             data);

    if (OpenGL::g_cached_gl_compressed_tex_image_3D == nullptr)
    {
        OpenGL::g_cached_gl_compressed_tex_image_3D = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glCompressedTexImage3D");
    }

    reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE3DPROC>(OpenGL::g_cached_gl_compressed_tex_image_3D)(target,
                                                                                                 level,
                                                                                                 internalformat,
                                                                                                 width,
                                                                                                 height,
                                                                                                 depth,
                                                                                                 border,
                                                                                                 imageSize,
                                                                                                 data);
}
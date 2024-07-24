/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_image_2d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCompressedTexImage2D(GLenum      target,
                                                GLint       level,
                                                GLenum      internalformat,
                                                GLsizei     width,
                                                GLsizei     height,
                                                GLint       border,
                                                GLsizei     imageSize,
                                                const void* data)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glCompressedTexImage2D(target=[%s] level=[%d] internalformat=[%s] width=[%d] height=[%d] border=[%d] imageSize=[%d] data=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
             static_cast<int32_t>(width),
             static_cast<int32_t>(height),
             border,
             imageSize,
             data);

    if (OpenGL::g_cached_gl_compressed_tex_image_2D == nullptr)
    {
        OpenGL::g_cached_gl_compressed_tex_image_2D = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glCompressedTexImage2D");
    }

    reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE2DPROC>(OpenGL::g_cached_gl_compressed_tex_image_2D)(target,
                                                                                                 level,
                                                                                                 internalformat,
                                                                                                 width,
                                                                                                 height,
                                                                                                 border,
                                                                                                 imageSize,
                                                                                                 data);
}
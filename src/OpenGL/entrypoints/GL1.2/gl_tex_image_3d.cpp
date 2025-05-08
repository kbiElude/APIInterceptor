/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.2/gl_tex_image_3d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexImage3D(GLenum      target,
                                      GLint       level,
                                      GLint       internalformat,
                                      GLsizei     width,
                                      GLsizei     height,
                                      GLsizei     depth,
                                      GLint       border,
                                      GLenum      format,
                                      GLenum      type,
                                      const void* pixels)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glTexImage3D(target=[%s] level={%d] internalformat=[%s] width=[%d] height=[%d] depth=[%d] border=[%d] format=[%s] type=[%s] pixels=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
             static_cast<int32_t>(width),
             static_cast<int32_t>(height),
             static_cast<int32_t>(depth),
             border,
             OpenGL::Utils::get_raw_string_for_gl_enum(format),
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             pixels);

    reinterpret_cast<PFNGLTEXIMAGE3DPROC>(OpenGL::g_cached_gl_tex_image_3D)(target,
                                                                            level,
                                                                            internalformat,
                                                                            width,
                                                                            height,
                                                                            depth,
                                                                            border,
                                                                            format,
                                                                            type,
                                                                            pixels);
}
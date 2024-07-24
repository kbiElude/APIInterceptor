/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_tex_image_1d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexImage1D(GLenum      target,
                                      GLint       level,
                                      GLint       internalformat,
                                      GLsizei     width,
                                      GLint       border,
                                      GLenum      format,
                                      GLenum      type,
                                      const void* pixels)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glTexImage1D(target=[%s] level=[%d] internalformat=[%s] width=[%d] border=[%d] format=[%s] type=[%s] pixels=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
             static_cast<int32_t>(width),
             border,
             OpenGL::Utils::get_raw_string_for_gl_enum(format),
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             pixels);

    if (OpenGL::g_cached_gl_tex_image_1D == nullptr)
    {
        OpenGL::g_cached_gl_tex_image_1D = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glTexImage1D");
    }

    reinterpret_cast<PFNGLTEXIMAGE1DPROC>(OpenGL::g_cached_gl_tex_image_1D)(target,
                                                                            level,
                                                                            internalformat,
                                                                            width,
                                                                            border,
                                                                            format,
                                                                            type,
                                                                            pixels);
}
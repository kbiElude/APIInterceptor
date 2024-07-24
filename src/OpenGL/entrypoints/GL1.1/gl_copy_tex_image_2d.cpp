/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_copy_tex_image_2d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCopyTexImage2D(GLenum  target,
                                          GLint   level,
                                          GLenum  internalformat,
                                          GLint   x,
                                          GLint   y,
                                          GLsizei width,
                                          GLsizei height,
                                          GLint   border)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glCopyTexImage2D(target=[%s] level=[%d] internalformat=[%s] x=[%d] y=[%d] width=[%d] height={%d] border=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
             x,
             y,
             static_cast<int32_t>(width),
             static_cast<int32_t>(height),
             border);

    if (OpenGL::g_cached_gl_copy_tex_image_2D == nullptr)
    {
        OpenGL::g_cached_gl_copy_tex_image_2D = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glCopyTexImage2D");
    }

    reinterpret_cast<PFNGLCOPYTEXIMAGE2DPROC>(OpenGL::g_cached_gl_copy_tex_image_2D)(target,
                                                                                     level,
                                                                                     internalformat,
                                                                                     x,
                                                                                     y,
                                                                                     width,
                                                                                     height,
                                                                                     border);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_copy_tex_sub_image_1d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCopyTexSubImage1D(GLenum  target,
                                             GLint   level,
                                             GLint   xoffset,
                                             GLint   x,
                                             GLint   y,
                                             GLsizei width)
{
    AI_TRACE("glCopyTexSubImage1D(target=[%s] level=[%d] xoffset=[%d] x=[%d] y=[%d] width=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             xoffset,
             x,
             y,
             static_cast<int32_t>(width) );

    if (OpenGL::g_cached_gl_copy_tex_sub_image_1D == nullptr)
    {
        OpenGL::g_cached_gl_copy_tex_sub_image_1D = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glCopyTexSubImage1D");
    }

    reinterpret_cast<PFNGLCOPYTEXSUBIMAGE1DPROC>(OpenGL::g_cached_gl_copy_tex_sub_image_1D)(target,
                                                                                            level,
                                                                                            xoffset,
                                                                                            x,
                                                                                            y,
                                                                                            width);
}
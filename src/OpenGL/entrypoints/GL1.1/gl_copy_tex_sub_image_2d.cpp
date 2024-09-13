/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_copy_tex_sub_image_2d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCopyTexSubImage2D(GLenum  target,
                                             GLint   level,
                                             GLint   xoffset,
                                             GLint   yoffset,
                                             GLint   x,
                                             GLint   y,
                                             GLsizei width,
                                             GLsizei height)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glCopyTexSubImage2D(target=[%s] level=[%d] xoffset=[%d] yoffset=[%d] x=[%d] y=[%d] width=[%d] height=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             xoffset,
             yoffset,
             x,
             y,
             static_cast<int32_t>(width),
             static_cast<int32_t>(height) );

    reinterpret_cast<PFNGLCOPYTEXSUBIMAGE2DPROC>(OpenGL::g_cached_gl_copy_tex_sub_image_2D)(target,
                                                                                            level,
                                                                                            xoffset,
                                                                                            yoffset,
                                                                                            x,
                                                                                            y,
                                                                                            width,
                                                                                            height);
}
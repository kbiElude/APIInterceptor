/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.2/gl_copy_tex_sub_image_3d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCopyTexSubImage3D(GLenum  target,
                                             GLint   level,
                                             GLint   xoffset,
                                             GLint   yoffset,
                                             GLint   zoffset,
                                             GLint   x,
                                             GLint   y,
                                             GLsizei width,
                                             GLsizei height)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glCopyTexSubImage3D(target=[%s] level=[%d] xoffset=[%d] yoffset=[%d] zoffset=[%d] x=[%d] y=[%d] width=[%d] height=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             xoffset,
             yoffset,
             zoffset,
             x,
             y,
             static_cast<int32_t>(width),
             static_cast<int32_t>(height) );

    reinterpret_cast<PFNGLCOPYTEXSUBIMAGE3DPROC>(OpenGL::g_cached_gl_copy_tex_sub_image_3D)(target,
                                                                                            level,
                                                                                            xoffset,
                                                                                            yoffset,
                                                                                            zoffset,
                                                                                            x,
                                                                                            y,
                                                                                            width,
                                                                                            height);
}
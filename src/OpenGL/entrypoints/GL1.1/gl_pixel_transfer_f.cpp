/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_pixel_transfer_f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPixelTransferf(GLenum  pname,
                                          GLfloat param)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glPixelTransferf(pname=[%s], param=[%.4f])",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             param);

    reinterpret_cast<PFNGLPIXELTRANSFERFPROC>(OpenGL::g_cached_gl_pixel_transfer_f)(pname,
                                                                                    param);
}
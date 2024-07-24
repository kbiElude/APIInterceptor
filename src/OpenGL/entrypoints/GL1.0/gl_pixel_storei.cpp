/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_pixel_storei.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPixelStorei(GLenum pname,
                                       GLint  param)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glPixelStorei(pname=[%s] param=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             param);

    if (OpenGL::g_cached_gl_pixel_storei == nullptr)
    {
        OpenGL::g_cached_gl_pixel_storei = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glPixelStorei");
    }

    reinterpret_cast<PFNGLPIXELSTOREIPROC>(g_cached_gl_pixel_storei)(pname,
                                                                     param);
}
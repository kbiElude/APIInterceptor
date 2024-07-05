/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_color_mask.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColorMask(GLboolean red,
                                     GLboolean green,
                                     GLboolean blue,
                                     GLboolean alpha)
{
    AI_TRACE("glColorMask(red=[%d] green=[%d] blue={%d] alpha=[%d])",
             (red   == GL_TRUE) ? 1 : 0,
             (green == GL_TRUE) ? 1 : 0,
             (blue  == GL_TRUE) ? 1 : 0,
             (alpha == GL_TRUE) ? 1 : 0);

    if (OpenGL::g_cached_gl_color_mask == nullptr)
    {
        OpenGL::g_cached_gl_color_mask = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glColorMask");
    }

    reinterpret_cast<PFNGLCOLORMASKPROC>(OpenGL::g_cached_gl_color_mask)(red,
                                                                         green,
                                                                         blue,
                                                                         alpha);
}
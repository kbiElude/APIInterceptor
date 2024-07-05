/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.4/gl_blend_color.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBlendColor(GLfloat red,
                                      GLfloat green,
                                      GLfloat blue,
                                      GLfloat alpha)
{
    AI_TRACE("glBlendColor(red=[%.4f] green=[%.4f] blue=[%.4f] alpha=[%.4f])",
             red,
             green,
             blue,
             alpha);

    if (OpenGL::g_cached_gl_blend_color == nullptr)
    {
        OpenGL::g_cached_gl_blend_color = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glBlendColor");
    }

    reinterpret_cast<PFNGLBLENDCOLORPROC>(OpenGL::g_cached_gl_blend_color)(red,
                                                                           green,
                                                                           blue,
                                                                           alpha);
}
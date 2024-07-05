/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_4i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor4i(GLint red,
                                   GLint green,
                                   GLint blue,
                                   GLint alpha)
{
    AI_TRACE("glaiColor4i(red=[%d] green=[%d] blue=[%d] alpha=[%d])",
             red,
             green,
             blue,
             alpha);

    reinterpret_cast<PFNGLCOLOR4IPROC>(OpenGL::g_cached_gl_color_4i)(red,
                                                                     green,
                                                                     blue,
                                                                     alpha);
}
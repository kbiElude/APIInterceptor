/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_3i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor3i(GLint red,
                                   GLint green,
                                   GLint blue)
{
    AI_TRACE("glColor3i(red=[%d] green=[%d] blue=[%d])",
             red,
             green,
             blue);

    reinterpret_cast<PFNGLCOLOR3IPROC>(OpenGL::g_cached_gl_color_3i)(red,
                                                                     green,
                                                                     blue);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_3d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor3d(GLdouble red,
                                   GLdouble green,
                                   GLdouble blue)
{
    AI_TRACE("glColor3d(red=[%.4lf] green=[%.4lf] blue=[%.4lf])",
             red,
             green,
             blue);

    reinterpret_cast<PFNGLCOLOR3DPROC>(OpenGL::g_cached_gl_color_3d)(red,
                                                                     green,
                                                                     blue);
}
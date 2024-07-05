/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_4d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor4d(GLdouble red,
                                   GLdouble green,
                                   GLdouble blue,
                                   GLdouble alpha)
{
    AI_TRACE("glColor4d(red=[%.4f] green=[%.4f] blue=[%.4f] alpha=[%.4f])",
             red,
             green,
             blue,
             alpha);

    reinterpret_cast<PFNGLCOLOR4DPROC>(OpenGL::g_cached_gl_color_4d)(red,
                                                                     green,
                                                                     blue,
                                                                     alpha);
}
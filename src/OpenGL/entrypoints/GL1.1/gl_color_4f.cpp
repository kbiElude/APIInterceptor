/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_4f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor4f(GLfloat red,
                                   GLfloat green,
                                   GLfloat blue,
                                   GLfloat alpha)
{
    AI_TRACE("glColor4f(red=[%.4f] green=[%.4f] blue=[%.4f] alpha=[%.4f])",
             red,
             green,
             blue,
             alpha);

    reinterpret_cast<PFNGLCOLOR4FPROC>(OpenGL::g_cached_gl_color_4f)(red,
                                                                     green,
                                                                     blue,
                                                                     alpha);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_3f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor3f(GLfloat red,
                                   GLfloat green,
                                   GLfloat blue)
{
    AI_TRACE("glColor3f(red=[%.4f] green=[%.4f] blue=[%.4f])",
             red,
             green,
             blue);

    reinterpret_cast<PFNGLCOLOR3FPROC>(OpenGL::g_cached_gl_color_3f)(red,
                                                                     green,
                                                                     blue);
}
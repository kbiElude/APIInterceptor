/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_3ui.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor3ui(GLuint red,
                                    GLuint green,
                                    GLuint blue)
{
    AI_TRACE("glColor3ui(red=[%d] green=[%d] blue=[%d])",
             red,
             green,
             blue);

    reinterpret_cast<PFNGLCOLOR3UIPROC>(OpenGL::g_cached_gl_color_3ui)(red,
                                                                       green,
                                                                       blue);
}
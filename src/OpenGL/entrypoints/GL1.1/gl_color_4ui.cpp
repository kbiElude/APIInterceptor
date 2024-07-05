/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_4ui.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor4ui(GLuint red,
                                    GLuint green,
                                    GLuint blue,
                                    GLuint alpha)
{
    AI_TRACE("glColor4ui(red=[%d] green=[%d] blue=[%d] alpha=[%d])",
             red,
             green,
             blue,
             alpha);

    reinterpret_cast<PFNGLCOLOR4UIPROC>(OpenGL::g_cached_gl_color_4ui)(red,
                                                                       green,
                                                                       blue,
                                                                       alpha);
}
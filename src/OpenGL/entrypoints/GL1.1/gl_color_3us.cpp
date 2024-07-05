/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_3us.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor3us(GLushort red,
                                    GLushort green,
                                    GLushort blue)
{
    AI_TRACE("glColor3us(red=[%d] green=[%d] blue=[%d])",
             static_cast<uint32_t>(red),
             static_cast<uint32_t>(green),
             static_cast<uint32_t>(blue) );

    reinterpret_cast<PFNGLCOLOR3USPROC>(OpenGL::g_cached_gl_color_3us)(red,
                                                                       green,
                                                                       blue);
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_4us.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor4us(GLushort red,
                                    GLushort green,
                                    GLushort blue,
                                    GLushort alpha)
{
    AI_TRACE("glColor4us(red=[%d] green=[%d] blue=[%d] alpha=[%d])",
             static_cast<uint32_t>(red),
             static_cast<uint32_t>(green),
             static_cast<uint32_t>(blue),
             static_cast<uint32_t>(alpha) );

    reinterpret_cast<PFNGLCOLOR4USPROC>(OpenGL::g_cached_gl_color_4us)(red,
                                                                       green,
                                                                       blue,
                                                                       alpha);
}
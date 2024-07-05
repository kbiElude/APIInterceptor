/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_4b.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor4b(GLbyte red,
                                   GLbyte green,
                                   GLbyte blue,
                                   GLbyte alpha)
{
    AI_TRACE("glColor4b(red=[%d] green=[%d] blue=[%d] alpha=[%d])",
             static_cast<uint32_t>(red),
             static_cast<uint32_t>(green),
             static_cast<uint32_t>(blue),
             static_cast<uint32_t>(alpha) );

    reinterpret_cast<PFNGLCOLOR4BPROC>(OpenGL::g_cached_gl_color_4b)(red,
                                                                     green,
                                                                     blue,
                                                                     alpha);
}
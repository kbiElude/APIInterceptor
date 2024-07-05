/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_4ub.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor4ub(GLubyte red,
                                    GLubyte green,
                                    GLubyte blue,
                                    GLubyte alpha)
{
    AI_TRACE("glColor4ub(red=[%d] green=[%d] blue=[%d] alpha=[%d])",
             static_cast<uint32_t>(red),
             static_cast<uint32_t>(green),
             static_cast<uint32_t>(blue),
             static_cast<uint32_t>(alpha) );

    reinterpret_cast<PFNGLCOLOR4UBPROC>(OpenGL::g_cached_gl_color_4ub)(red,
                                                                       green,
                                                                       blue,
                                                                       alpha);
}
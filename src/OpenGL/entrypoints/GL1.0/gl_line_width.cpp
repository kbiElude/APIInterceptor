/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_line_width.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiLineWidth(GLfloat width)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glLineWidth(width=[%.4f])",
             width);

    reinterpret_cast<PFNGLLINEWIDTHPROC>(OpenGL::g_cached_gl_line_width)(width);
}
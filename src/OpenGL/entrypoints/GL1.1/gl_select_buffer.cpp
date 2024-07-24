/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_select_buffer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiSelectBuffer(GLsizei size,
                                        GLuint* buffer)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glSelectBuffer(size=[%d], buffer=[%p])",
             size,
             buffer);

    reinterpret_cast<PFNGLSELECTBUFFERPROC>(OpenGL::g_cached_gl_select_buffer)(size,
                                                                               buffer);
}
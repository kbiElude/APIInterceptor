/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.5/gl_gen_buffers.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGenBuffers(GLsizei n,
                                      GLuint* buffers)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGenBuffers(n=[%d] buffers=[%p])",
             static_cast<int32_t>(n),
             buffers);

    reinterpret_cast<PFNGLGENBUFFERSPROC>(OpenGL::g_cached_gl_gen_buffers)(n,
                                                                           buffers);
}
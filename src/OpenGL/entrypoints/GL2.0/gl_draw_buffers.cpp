/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_draw_buffers.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawBuffers(GLsizei       n,
                                       const GLenum* bufs)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glDrawBuffers(n=[%d] bufs=[%p]",
             static_cast<int32_t>(n),
             bufs); /* todo: expand to a list of buf enums */

    if (OpenGL::g_cached_gl_draw_buffers == nullptr)
    {
        OpenGL::g_cached_gl_draw_buffers = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDrawBuffers");
    }

    reinterpret_cast<PFNGLDRAWBUFFERSPROC>(OpenGL::g_cached_gl_draw_buffers)(n,
                                                                             bufs);
}
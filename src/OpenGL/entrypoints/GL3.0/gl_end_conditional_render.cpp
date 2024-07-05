/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_end_conditional_render.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEndConditionalRender(void)
{
    AI_TRACE("glEndConditionalRender()");

    if (OpenGL::g_cached_gl_end_conditional_render == nullptr)
    {
        OpenGL::g_cached_gl_end_conditional_render = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glEndConditionalRender");
    }

    reinterpret_cast<PFNGLENDCONDITIONALRENDERPROC>(OpenGL::g_cached_gl_end_conditional_render)();
}
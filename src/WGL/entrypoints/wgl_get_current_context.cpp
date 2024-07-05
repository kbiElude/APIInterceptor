/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/globals.h"
#include "WGL/globals.h"
#include "WGL/entrypoints/wgl_get_current_context.h"

HGLRC WINAPI WGL::get_current_context()
{
    AI_TRACE("wglGetCurrentContext()");

    return reinterpret_cast<PFNWGLGETCURRENTCONTEXTPROC>(WGL::g_cached_get_current_context_func_ptr)();
}

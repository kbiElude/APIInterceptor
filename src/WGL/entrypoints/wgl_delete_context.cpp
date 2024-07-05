/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/globals.h"
#include "WGL/entrypoints/wgl_delete_context.h"
#include "WGL/globals.h"

BOOL WINAPI WGL::delete_context(HGLRC in_hglrc)
{
    AI_TRACE("wglDeleteContext(in_hglrc=[%p])",
               in_hglrc);

    return reinterpret_cast<PFNWGLDELETECONTEXTPROC>(WGL::g_cached_delete_context_func_ptr)(in_hglrc);
}

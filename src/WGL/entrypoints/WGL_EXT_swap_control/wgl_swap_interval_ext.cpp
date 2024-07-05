/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/globals.h"
#include "WGL/entrypoints/WGL_EXT_swap_control/wgl_swap_interval_ext.h"
#include "WGL/globals.h"
#include "WGL/utils_trace.h"

BOOL WINAPI WGL::swap_interval_ext(int in_interval)
{
    AI_TRACE("wglSwapIntervalEXT(in_interval=[%d])\n",
               in_interval);

    if (WGL::g_cached_swap_interval_ext_func_ptr == nullptr)
    {
        WGL::g_cached_swap_interval_ext_func_ptr = reinterpret_cast<PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("wglSwapIntervalEXT");

        AI_ASSERT(WGL::g_cached_swap_interval_ext_func_ptr != nullptr);
    }

    return reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>(WGL::g_cached_swap_interval_ext_func_ptr)(in_interval);
}

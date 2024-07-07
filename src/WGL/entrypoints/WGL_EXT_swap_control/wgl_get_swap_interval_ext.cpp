/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/globals.h"
#include "WGL/entrypoints/WGL_EXT_swap_control/wgl_get_swap_interval_ext.h"
#include "WGL/globals.h"
#include "WGL/utils_trace.h"

int WINAPI WGL::get_swap_interval_ext()
{
    AI_TRACE("wglGetSwapIntervalEXT()\n");

    return reinterpret_cast<PFNWGLGETSWAPINTERVALEXTPROC>(WGL::g_cached_get_swap_interval_ext_func_ptr)();
}

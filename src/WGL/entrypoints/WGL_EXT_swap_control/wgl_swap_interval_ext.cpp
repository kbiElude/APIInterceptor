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

    return reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>(WGL::g_cached_swap_interval_ext_func_ptr)(in_interval);
}

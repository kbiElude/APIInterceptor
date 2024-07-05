/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/globals.h"
#include "WGL/globals.h"
#include "WGL/entrypoints/wgl_get_current_dc.h"

HDC WINAPI WGL::get_current_dc()
{
    AI_TRACE("wglGetCurrentDC()");

    return reinterpret_cast<PFNWGLGETCURRENTDCPROC>(WGL::g_cached_get_current_dc_func_ptr)();
}

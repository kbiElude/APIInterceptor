/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/globals.h"
#include "WGL/entrypoints/WGL_ARB_extensions_string/wgl_get_extensions_string_arb.h"
#include "WGL/globals.h"
#include "WGL/utils_trace.h"

const char* WINAPI WGL::get_extensions_string_arb(HDC in_hdc)
{
    AI_TRACE("wglGetExtensionsStringARB(in_hdc = [%p])\n",
               in_hdc);

    return reinterpret_cast<PFNWGLGETEXTENSIONSSTRINGARGPROC>(WGL::g_cached_get_extensions_string_arb_func_ptr)(in_hdc);
}

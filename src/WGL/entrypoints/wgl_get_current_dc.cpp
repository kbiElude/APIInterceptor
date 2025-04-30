/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "WGL/globals.h"
#include "WGL/entrypoints/wgl_get_current_dc.h"

HDC WINAPI WGL::get_current_dc()
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    HDC                                 result              = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("wglGetCurrentDC()");

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLGETCURRENTDC,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLGETCURRENTDC,
                          0,       /* in_n_args   */
                          nullptr, /* in_args_ptr */
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNWGLGETCURRENTDCPROC>(WGL::g_cached_get_current_dc_func_ptr)();
    }

    return result;
}

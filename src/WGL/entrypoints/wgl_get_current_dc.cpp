/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "WGL/globals.h"
#include "WGL/entrypoints/wgl_get_current_dc.h"

HDC WINAPI WGL::get_current_dc()
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    HDC                                     result                 = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("wglGetCurrentDC()");

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLGETCURRENTDC,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLGETCURRENTDC,
                                  0,       /* in_n_args   */
                                  nullptr, /* in_args_ptr */
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNWGLGETCURRENTDCPROC>(WGL::g_cached_get_current_dc_func_ptr)();
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLGETCURRENTDC,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const auto result_arg = APIInterceptor::APIFunctionArgument::create_void_ptr(result);

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLGETCURRENTDC,
                                   post_callback_func_arg,
                                  &result_arg);
        }
    }

    return result;
}

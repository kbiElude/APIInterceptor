/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "User32/globals.h"
#include "User32/entrypoints/release_dc.h"

int WINAPI User32::release_dc(HWND in_hwnd,
                              HDC  in_hdc)
{
    void*                                   post_callback_func_arg  = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr  = nullptr;
    void*                                   pre_callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr   = nullptr;
    int                                     result                  = 0;
    bool                                    should_pass_through     = true;

    /* NOTE: We do NOT use a Tracker instance to track this call. The reason is drivers often call ReleaseDC() from driver-managed
     * threads, and being able to track these DC allocations is important.
     **/

    AI_TRACE("ReleaseDC(in_hwnd=[%p] in_hdc=[%p])\n",
             in_hwnd,
             in_hdc);

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_USER32_RELEASEDC,
                                                     &pre_callback_func_ptr,
                                                     &pre_callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hwnd),
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hdc),
        };

        pre_callback_func_ptr(APIInterceptor::APIFUNCTION_USER32_RELEASEDC,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<User32::PFNRELEASEDCPROC>(User32::g_cached_release_dc_func_ptr)(in_hwnd,
                                                                                                  in_hdc);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_USER32_RELEASEDC,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        const auto result_arg = APIInterceptor::APIFunctionArgument::create_i32(result);

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_USER32_RELEASEDC,
                               post_callback_func_arg,
                              &result_arg);
    }

    return result;
}

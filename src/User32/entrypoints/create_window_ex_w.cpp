/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "User32/globals.h"
#include "User32/entrypoints/create_window_ex_w.h"

HWND WINAPI User32::create_window_ex_w(DWORD     in_ex_style,
                                       LPCWSTR   in_class_name_ptr,
                                       LPCWSTR   in_window_name_ptr,
                                       DWORD     in_style,
                                       int       in_x,
                                       int       in_y,
                                       int       in_width,
                                       int       in_height,
                                       HWND      in_hwnd_parent,
                                       HMENU     in_hmenu,
                                       HINSTANCE in_hinstance,
                                       LPVOID    in_param_ptr)
{
    void*                                   post_callback_func_arg  = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr  = nullptr;
    void*                                   pre_callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr   = nullptr;
    HWND                                    result                  = 0;
    bool                                    should_pass_through     = true;

    AI_TRACE("CreateWindowExW(\n"
             " in_ex_style                    = [%d]\n"
             " in_class_name_ptr              = [%p]\n"
             " in_window_name_ptr             = [%p]\n"
             " in_style                       = [%d]\n"
             " in_x                           = [%d]\n"
             " in_y                           = [%d]\n"
             " in_width                       = [%d]\n"
             " in_height                      = [%d]\n"
             " in_hwnd_parent                 = [%p]\n"
             " in_hmenu                       = [%p]\n"
             " in_hinstance                   = [%p]\n"
             " in_param_ptr                   = [%p])\n",
             in_ex_style,
             in_class_name_ptr,
             in_window_name_ptr,
             in_style,
             in_x,
             in_y,
             in_width,
             in_height,
             in_hwnd_parent,
             in_hmenu,
             in_hinstance,
             in_param_ptr);

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_USER32_CREATEWINDOWEXW,
                                                     &pre_callback_func_ptr,
                                                     &pre_callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32     (in_ex_style),
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_class_name_ptr),
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_window_name_ptr),
            APIInterceptor::APIFunctionArgument::create_u32     (in_style),
            APIInterceptor::APIFunctionArgument::create_u32     (in_x),
            APIInterceptor::APIFunctionArgument::create_u32     (in_y),
            APIInterceptor::APIFunctionArgument::create_u32     (in_width),
            APIInterceptor::APIFunctionArgument::create_u32     (in_height),
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hwnd_parent),
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hmenu),
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hinstance),
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_param_ptr)
        };

        pre_callback_func_ptr(APIInterceptor::APIFUNCTION_USER32_CREATEWINDOWEXW,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<User32::PFNCREATEWINDOWEXWPROC>(User32::g_cached_create_window_ex_w_func_ptr)(in_ex_style,
                                                                                                                in_class_name_ptr,
                                                                                                                in_window_name_ptr,
                                                                                                                in_style,
                                                                                                                in_x,
                                                                                                                in_y,
                                                                                                                in_width,
                                                                                                                in_height,
                                                                                                                in_hwnd_parent,
                                                                                                                in_hmenu,
                                                                                                                in_hinstance,
                                                                                                                in_param_ptr);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_USER32_CREATEWINDOWEXW,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        const auto result_arg = APIInterceptor::APIFunctionArgument::create_void_ptr(result);

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_USER32_CREATEWINDOWEXW,
                               post_callback_func_arg,
                               0,       /* in_n_args_out   */
                               nullptr, /* in_args_out_ptr */
                              &result_arg);
    }

    return result;
}

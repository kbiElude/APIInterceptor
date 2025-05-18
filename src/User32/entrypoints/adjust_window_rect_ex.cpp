/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "User32/globals.h"
#include "User32/entrypoints/adjust_window_rect_ex.h"

BOOL WINAPI User32::adjust_window_rect_ex(LPRECT in_rect_ptr,
                                          DWORD  in_style,
                                          BOOL   in_menu,
                                          DWORD  in_ex_style)
{
    void*                                   post_callback_func_arg  = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr  = nullptr;
    void*                                   pre_callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr   = nullptr;
    BOOL                                    result                  = 0;
    bool                                    should_pass_through     = true;

    AI_TRACE("AdjustWindowRectEx(lpRect=[%p], dwStyle=[%d], bMenu=[%d], dwExStyle=[%d])\n"
             in_rect_ptr,
             static_cast<uint32_t>(in_style),
             static_cast<uint32_t>(in_menu),
             static_cast<uint32_t>(in_ex_style) );

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_USER32_ADJUSTWINDOWRECTEX,
                                                     &pre_callback_func_ptr,
                                                     &pre_callback_func_arg) )
    {
        const auto rect_data_chunk_id = APIInterceptor::register_data_chunk(in_rect_ptr,
                                                                            (in_rect_ptr != nullptr) ? sizeof(RECT)
                                                                                                     : 0);

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(rect_data_chunk_id),
            APIInterceptor::APIFunctionArgument::create_u32          (in_style),
            APIInterceptor::APIFunctionArgument::create_i32          (in_menu),
            APIInterceptor::APIFunctionArgument::create_u32          (in_ex_style),
        };

        pre_callback_func_ptr(APIInterceptor::APIFUNCTION_USER32_ADJUSTWINDOWRECTEX,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<User32::PFNADJUSTWINDOWRECTEXPROC>(User32::g_cached_adjust_window_rect_ex_func_ptr)(in_rect_ptr,
                                                                                                                     in_style,
                                                                                                                     in_menu,
                                                                                                                     in_ex_style);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_USER32_ADJUSTWINDOWRECTEX,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        const auto result_arg = APIInterceptor::APIFunctionArgument::create_i32(result);

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_USER32_ADJUSTWINDOWRECTEX,
                               post_callback_func_arg,
                              &result_arg);
    }

    return result;
}

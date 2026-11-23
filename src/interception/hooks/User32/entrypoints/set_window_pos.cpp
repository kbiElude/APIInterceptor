/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/callbacks.h"
#include "common/gate_scope.h"
#include "common/globals.h"
#include "common/logger.h"
#include "common/macros.h"
#include "interception/hooks/User32/globals.h"
#include "interception/hooks/User32/entrypoints/set_window_pos.h"

BOOL WINAPI Interception::Hooks::User32::set_window_pos(HWND in_hwnd,
                                                        HWND in_hwnd_insert_after,
                                                        int  in_x,
                                                        int  in_y,
                                                        int  in_cx,
                                                        int  in_cy,
                                                        UINT in_flags)
{
    APIInterceptor::GateScope               gate_scope;
    void*                                   post_callback_func_arg  = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr  = nullptr;
    void*                                   pre_callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr   = nullptr;
    BOOL                                    result                  = 0;
    bool                                    should_pass_through     = true;

    AI_TRACE("SetWindowPos(hWnd=[%p], hWndInsertAfter=[%p], X=[%d], Y=[%d], cx=[%d], cy=[%d], uFlags=[%u])\n",
             in_hwnd,
             in_hwnd_insert_after,
             in_x,
             in_y,
             in_cx,
             in_cy,
             static_cast<uint32_t>(in_flags) );

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_USER32_SETWINDOWPOS,
                                                     &pre_callback_func_ptr,
                                                     &pre_callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hwnd),
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hwnd_insert_after),
            APIInterceptor::APIFunctionArgument::create_i32     (in_x),
            APIInterceptor::APIFunctionArgument::create_i32     (in_y),
            APIInterceptor::APIFunctionArgument::create_i32     (in_cx),
            APIInterceptor::APIFunctionArgument::create_i32     (in_cy),
            APIInterceptor::APIFunctionArgument::create_u32     (in_flags),
        };

        pre_callback_func_ptr(APIInterceptor::APIFUNCTION_USER32_SETWINDOWPOS,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<Interception::Hooks::User32::PFNSETWINDOWPOSPROC>(Interception::Hooks::User32::g_cached_set_window_pos_func_ptr)(in_hwnd,
                                                                                                                                                  in_hwnd_insert_after,
                                                                                                                                                  in_x,
                                                                                                                                                  in_y,
                                                                                                                                                  in_cx,
                                                                                                                                                  in_cy,
                                                                                                                                                  in_flags);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_USER32_SETWINDOWPOS,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        /* After the call the window has the size the program meant for its area for drawing, whatever frame it has: the frame depends on the system and on whether
         * the program is DPI-aware, so the replay cannot work the area out from the outer size. It is given as the two arguments after the arguments of the call.
         */
        RECT       client          = {};
        const BOOL is_client_known = ::GetClientRect(in_hwnd,
                                                    &client);

        if (is_client_known == FALSE)
        {
            client = RECT();
        }

        const auto result_arg = APIInterceptor::APIFunctionArgument::create_i32(result);

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hwnd),
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hwnd_insert_after),
            APIInterceptor::APIFunctionArgument::create_i32     (in_x),
            APIInterceptor::APIFunctionArgument::create_i32     (in_y),
            APIInterceptor::APIFunctionArgument::create_i32     (in_cx),
            APIInterceptor::APIFunctionArgument::create_i32     (in_cy),
            APIInterceptor::APIFunctionArgument::create_u32     (in_flags),
            APIInterceptor::APIFunctionArgument::create_i32     (client.right  - client.left),
            APIInterceptor::APIFunctionArgument::create_i32     (client.bottom - client.top),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_USER32_SETWINDOWPOS,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }

    return result;
}

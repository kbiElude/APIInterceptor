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
#include "interception/hooks/User32/entrypoints/move_window.h"

BOOL WINAPI Interception::Hooks::User32::move_window(HWND in_hwnd,
                                                     int  in_x,
                                                     int  in_y,
                                                     int  in_width,
                                                     int  in_height,
                                                     BOOL in_repaint)
{
    APIInterceptor::GateScope               gate_scope;
    void*                                   post_callback_func_arg  = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr  = nullptr;
    void*                                   pre_callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr   = nullptr;
    BOOL                                    result                  = 0;
    bool                                    should_pass_through     = true;

    AI_TRACE("MoveWindow(hWnd=[%p], X=[%d], Y=[%d], nWidth=[%d], nHeight=[%d], bRepaint=[%d])\n",
             in_hwnd,
             in_x,
             in_y,
             in_width,
             in_height,
             static_cast<int>(in_repaint) );

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_USER32_MOVEWINDOW,
                                                     &pre_callback_func_ptr,
                                                     &pre_callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hwnd),
            APIInterceptor::APIFunctionArgument::create_i32     (in_x),
            APIInterceptor::APIFunctionArgument::create_i32     (in_y),
            APIInterceptor::APIFunctionArgument::create_i32     (in_width),
            APIInterceptor::APIFunctionArgument::create_i32     (in_height),
            APIInterceptor::APIFunctionArgument::create_i32     (in_repaint),
        };

        pre_callback_func_ptr(APIInterceptor::APIFUNCTION_USER32_MOVEWINDOW,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<Interception::Hooks::User32::PFNMOVEWINDOWPROC>(Interception::Hooks::User32::g_cached_move_window_func_ptr)(in_hwnd,
                                                                                                                                              in_x,
                                                                                                                                              in_y,
                                                                                                                                              in_width,
                                                                                                                                              in_height,
                                                                                                                                              in_repaint);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_USER32_MOVEWINDOW,
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
            APIInterceptor::APIFunctionArgument::create_i32     (in_x),
            APIInterceptor::APIFunctionArgument::create_i32     (in_y),
            APIInterceptor::APIFunctionArgument::create_i32     (in_width),
            APIInterceptor::APIFunctionArgument::create_i32     (in_height),
            APIInterceptor::APIFunctionArgument::create_i32     (in_repaint),
            APIInterceptor::APIFunctionArgument::create_i32     (client.right  - client.left),
            APIInterceptor::APIFunctionArgument::create_i32     (client.bottom - client.top),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_USER32_MOVEWINDOW,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }

    return result;
}

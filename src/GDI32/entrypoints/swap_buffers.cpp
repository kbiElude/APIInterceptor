/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "GDI32/entrypoints/swap_buffers.h"
#include "GDI32/globals.h"

BOOL WINAPI GDI32::swap_buffers(HDC in_hdc)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    BOOL                                    result                 = TRUE;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("SwapBuffers(in_hdc=[%p])",
                 in_hdc);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_void_ptr(in_hdc)
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    APIInterceptor::g_logger_ptr->on_frame_presented();

    if (should_pass_through)
    {
        result = reinterpret_cast<GDI32::PFNSWAPBUFFERSPROC>(GDI32::g_cached_swap_buffers_func_ptr)(in_hdc);
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const auto result_arg = APIInterceptor::APIFunctionArgument::create_i32(result);

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS,
                                   post_callback_func_arg,
                                  &result_arg);
        }
    }

    return result;
}
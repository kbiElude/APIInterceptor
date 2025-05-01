/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "GDI32/entrypoints/swap_buffers.h"
#include "GDI32/globals.h"

BOOL WINAPI GDI32::swap_buffers(HDC in_hdc)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;

    AI_TRACE("SwapBuffers(in_hdc=[%p])",
             in_hdc);

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS,
                                                     &callback_func_ptr,
                                                     &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hdc)
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    APIInterceptor::g_logger_ptr->on_frame_presented();

    if (should_pass_through)
    {
        return reinterpret_cast<GDI32::PFNSWAPBUFFERSPROC>(GDI32::g_cached_swap_buffers_func_ptr)(in_hdc);
    }
    else
    {
        return TRUE;
    }
}
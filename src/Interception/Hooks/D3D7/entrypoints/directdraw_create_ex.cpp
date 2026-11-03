/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "Interception/Hooks/D3D7/argument_capture.h"
#include "Interception/Hooks/D3D7/entrypoints.h"
#include "Interception/Hooks/D3D7/globals.h"
#include "Interception/Hooks/D3D7/hook_table.h"

HRESULT __stdcall Interception::Hooks::D3D7::aiDirectDrawCreateEx(GUID*       in_guid_ptr,
                                                                  void**      out_direct_draw_ptr_ptr,
                                                                  const GUID& in_iid,
                                                                  IUnknown*   in_outer_ptr)
{
    /* IID_IDirectDraw7 */
    static const GUID IID_DIRECT_DRAW7 = {0x15e65ec0, 0x3b9c, 0x11d2, {0xb9, 0x2f, 0x00, 0x60, 0x97, 0x97, 0xea, 0x5b} };

    constexpr uint32_t N_ARGUMENTS = 4;

    void*                                   post_callback_function_argument = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_function_ptr      = nullptr;
    void*                                   pre_callback_function_argument  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_function_ptr       = nullptr;
    HRESULT                                 result                          = E_FAIL;
    bool                                    should_pass_through             = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("DirectDrawCreateEx(guid=[%p] out=[%p] outer=[%p])",
                 in_guid_ptr,
                 out_direct_draw_ptr_ptr,
                 in_outer_ptr);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATEEX,
                                                         &pre_callback_function_ptr,
                                                         &pre_callback_function_argument) )
        {
            const APIInterceptor::APIFunctionArgument arguments[N_ARGUMENTS] =
            {
                ArgumentCapture<GUID*>::create_pre_argument      (in_guid_ptr),
                ArgumentCapture<void**>::create_pre_argument     (out_direct_draw_ptr_ptr),
                ArgumentCapture<const GUID&>::create_pre_argument(in_iid),
                ArgumentCapture<IUnknown*>::create_pre_argument  (in_outer_ptr)
            };

            pre_callback_function_ptr(APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATEEX,
                                      N_ARGUMENTS,
                                      arguments,
                                      pre_callback_function_argument,
                                     &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNDIRECTDRAWCREATEEXPROC>(g_direct_draw_create_ex_export_hook.get_original_function_ptr() )(in_guid_ptr,
                                                                                                                              out_direct_draw_ptr_ptr,
                                                                                                                              in_iid,
                                                                                                                              in_outer_ptr);
    }

    /* Hook the methods of IDirectDraw7. The other interfaces of DirectDraw are not described. */
    if (SUCCEEDED(result)                 &&
        out_direct_draw_ptr_ptr != nullptr &&
       *out_direct_draw_ptr_ptr != nullptr)
    {
        if (::IsEqualGUID(in_iid,
                          IID_DIRECT_DRAW7) )
        {
            get_hook_table_ptr()->patch_object(static_cast<uint32_t>(Interface::IDIRECTDRAW7),
                                              *out_direct_draw_ptr_ptr);
        }
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATEEX,
                                                          &post_callback_function_ptr,
                                                          &post_callback_function_argument) )
        {
            const APIInterceptor::APIFunctionArgument arguments[N_ARGUMENTS] =
            {
                ArgumentCapture<GUID*>::create_pre_argument      (in_guid_ptr),
                ArgumentCapture<void**>::create_post_argument    (out_direct_draw_ptr_ptr,
                                                                  APIInterceptor::APIFunctionArgument(),
                                                                  false /* in_is_pre_argument_valid */),
                ArgumentCapture<const GUID&>::create_pre_argument(in_iid),
                ArgumentCapture<IUnknown*>::create_pre_argument  (in_outer_ptr)
            };
            const auto result_argument = ArgumentCapture<HRESULT>::create_pre_argument(result);

            post_callback_function_ptr(APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATEEX,
                                       post_callback_function_argument,
                                       N_ARGUMENTS,
                                       arguments,
                                      &result_argument);
        }
    }

    return result;
}

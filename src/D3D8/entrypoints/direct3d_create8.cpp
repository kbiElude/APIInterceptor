/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "D3D8/entrypoints.h"
#include "D3D8/globals.h"
#include "D3D8/hook_table.h"

D3D8::IDirect3D8* __stdcall D3D8::aiDirect3DCreate8(UINT in_sdk_version)
{
    void*                                   post_callback_function_argument = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_function_ptr      = nullptr;
    void*                                   pre_callback_function_argument  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_function_ptr       = nullptr;
    IDirect3D8*                             result                          = nullptr;
    bool                                    should_pass_through             = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("Direct3DCreate8(in_sdk_version=[%u])",
                 in_sdk_version);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_D3D8_DIRECT3DCREATE8,
                                                         &pre_callback_function_ptr,
                                                         &pre_callback_function_argument) )
        {
            const APIInterceptor::APIFunctionArgument arguments[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32(in_sdk_version)
            };

            pre_callback_function_ptr(APIInterceptor::APIFUNCTION_D3D8_DIRECT3DCREATE8,
                                      sizeof(arguments) / sizeof(arguments[0]),
                                      arguments,
                                      pre_callback_function_argument,
                                     &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNDIRECT3DCREATE8PROC>(g_cached_direct3d_create8_function_ptr)(in_sdk_version);
    }

    /* Hook the methods of IDirect3D8. */
    HookTable::get_ptr()->patch_object(Interface::IDIRECT3D8,
                                       result);

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_D3D8_DIRECT3DCREATE8,
                                                          &post_callback_function_ptr,
                                                          &post_callback_function_argument) )
        {
            const auto result_argument = APIInterceptor::APIFunctionArgument::create_void_ptr(result);

            post_callback_function_ptr(APIInterceptor::APIFUNCTION_D3D8_DIRECT3DCREATE8,
                                       post_callback_function_argument,
                                       0,       /* in_n_args_out   */
                                       nullptr, /* in_args_out_ptr */
                                      &result_argument);
        }
    }

    return result;
}

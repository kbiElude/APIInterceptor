/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "User32/globals.h"
#include "User32/entrypoints/create_dc_a.h"

HDC WINAPI User32::create_dc_a(LPCSTR          in_driver_ptr,
                               LPCSTR          in_device_ptr,
                               LPCSTR          in_port_ptr,
                               const DEVMODEA* in_devmode_ptr)
{
    void*                                   post_callback_func_arg  = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr  = nullptr;
    void*                                   pre_callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr   = nullptr;
    HDC                                     result                  = 0;
    bool                                    should_pass_through     = true;

    /* NOTE: We do NOT use a Tracker instance to track this call. The reason is drivers often call CreateDCA() and later call it
     *       from driver-managed threads, and being able to track these DC allocations is important.
     **/
    AI_TRACE("CreateDCA(pwszDriver=[%p], pwszDevice=[%p], pszPort=[%p], pdm=[%p])\n"
             in_driver_ptr,
             in_device_ptr,
             in_port_ptr,
             in_devmode_ptr);

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_USER32_CREATEDCA,
                                                     &pre_callback_func_ptr,
                                                     &pre_callback_func_arg) )
    {
        const auto devmode_data_chunk_id = APIInterceptor::register_data_chunk(in_devmode_ptr,
                                                                               (in_devmode_ptr != nullptr) ? sizeof(DEVMODEA)
                                                                                                           : 0);

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr     (in_device_ptr),
            APIInterceptor::APIFunctionArgument::create_void_ptr     (in_port_ptr),
            APIInterceptor::APIFunctionArgument::create_void_ptr     (in_driver_ptr),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(devmode_data_chunk_id),
        };

        pre_callback_func_ptr(APIInterceptor::APIFUNCTION_USER32_CREATEDCA,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<User32::PFNCREATEDCAPROC>(User32::g_cached_create_dc_a_func_ptr)(in_driver_ptr,
                                                                                                   in_device_ptr,
                                                                                                   in_port_ptr,
                                                                                                   in_devmode_ptr);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_USER32_CREATEDCA,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        const auto result_arg = APIInterceptor::APIFunctionArgument::create_void_ptr(result);

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_USER32_CREATEDCA,
                               post_callback_func_arg,
                              &result_arg);
    }

    return result;
}

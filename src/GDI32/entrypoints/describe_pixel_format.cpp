/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/macros.h"
#include "GDI32/globals.h"
#include "GDI32/entrypoints/describe_pixel_format.h"

int WINAPI GDI32::describe_pixel_format(HDC                     in_hdc,
                                        int                     in_n_pixel_format,
                                        UINT                    in_n_bytes,
                                        LPPIXELFORMATDESCRIPTOR out_pixel_format_descriptor_ptr)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    int                                     result                 = 0;
    bool                                    should_pass_through    = true;

    AI_TRACE("DescribePixelFormat(in_hdc=[%p], in_n_pixel_format=[%d], in_n_bytes=[%d], out_pixel_format_descriptor_ptr=[%p])",
             in_hdc,
             in_n_pixel_format,
             in_n_bytes,
             out_pixel_format_descriptor_ptr);

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GDI32_DESCRIBEPIXELFORMAT,
                                                     &pre_callback_func_ptr,
                                                     &pre_callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hdc),
            APIInterceptor::APIFunctionArgument::create_i32     (in_n_pixel_format),
            APIInterceptor::APIFunctionArgument::create_u32     (in_n_bytes),
            APIInterceptor::APIFunctionArgument::create_void_ptr(out_pixel_format_descriptor_ptr),
        };

        pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GDI32_DESCRIBEPIXELFORMAT,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<GDI32::PFNDESCRIBEPIXELFORMATPROC>(GDI32::g_cached_describe_pixel_format_func_ptr)(in_hdc,
                                                                                                                     in_n_pixel_format,
                                                                                                                     in_n_bytes,
                                                                                                                     out_pixel_format_descriptor_ptr);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GDI32_DESCRIBEPIXELFORMAT,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        const auto result_arg = APIInterceptor::APIFunctionArgument::create_i32(result);

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GDI32_DESCRIBEPIXELFORMAT,
                               post_callback_func_arg,
                              &result_arg);
    }

    return result;
}
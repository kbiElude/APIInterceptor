/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "GDI32/entrypoints/get_pixel_format.h"
#include "GDI32/globals.h"

int WINAPI GDI32::get_pixel_format(HDC in_hdc)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    int                                 result              = 0;
    bool                                should_pass_through = true;

    AI_TRACE("GetPixelFormat(in_hdc=[%p])",
             in_hdc);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GDI32_GETPIXELFORMAT,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hdc),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GDI32_GETPIXELFORMAT,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<GDI32::PFNGETPIXELFORMATPROC>(GDI32::g_cached_get_pixel_format_func_ptr)(in_hdc);
    }

    return result;
}
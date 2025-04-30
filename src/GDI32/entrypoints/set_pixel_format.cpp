/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/macros.h"
#include "GDI32/entrypoints/set_pixel_format.h"
#include "GDI32/globals.h"
#include "GDI32/utils_trace.h"

BOOL WINAPI GDI32::set_pixel_format(HDC                          in_hdc,
                                    int                          in_format,
                                    CONST PIXELFORMATDESCRIPTOR* in_pixel_format_descriptor_ptr)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    BOOL                                result              = false;
    bool                                should_pass_through = true;

    AI_TRACE("SetPixelFormat(\n"
             " in_hdc=[%p]\n"
             " in_format=[%d]\n"
             " in_pixel_format_descriptor_ptr=%s)",
             in_hdc,
             in_format,
             GDI32::convert_pixel_format_descriptor_to_raw_string(in_pixel_format_descriptor_ptr) );

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GDI32_SETPIXELFORMAT,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hdc),
            APIInterceptor::APIFunctionArgument::create_i32     (in_format),
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_pixel_format_descriptor_ptr),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLATTACHSHADER,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<GDI32::PFNSETPIXELFORMATPROC>(GDI32::g_cached_set_pixel_format_func_ptr)(in_hdc,
                                                                                                           in_format,
                                                                                                           in_pixel_format_descriptor_ptr);
    }

    return result;
}
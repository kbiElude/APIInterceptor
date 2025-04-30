/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "WGL/entrypoints/WGL_ARB_extensions_string/wgl_get_extensions_string_arb.h"
#include "WGL/globals.h"
#include "WGL/utils_trace.h"

const char* WINAPI WGL::get_extensions_string_arb(HDC in_hdc)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    const char*                         result              = "?!";
    bool                                should_pass_through = true;

    AI_TRACE("wglGetExtensionsStringARB(in_hdc = [%p])\n",
               in_hdc);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLGETEXTENSIONSSTRINGARB,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hdc),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLGETEXTENSIONSSTRINGARB,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNWGLGETEXTENSIONSSTRINGARGPROC>(WGL::g_cached_get_extensions_string_arb_func_ptr)(in_hdc);
    }

    return result;
}

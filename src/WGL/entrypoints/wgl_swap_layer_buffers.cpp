/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "WGL/globals.h"
#include "WGL/entrypoints/wgl_swap_layer_buffers.h"

BOOL WINAPI WGL::swap_layer_buffers(HDC  in_hdc,
                                    UINT in_planes)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    BOOL                                result              = false;
    bool                                should_pass_through = true;

    AI_TRACE("wglSwapLayerBuffers(in_hdc=[%p] in_planes=[%d])",
               in_hdc,
               in_planes);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLSWAPLAYERBUFFERS,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hdc),
            APIInterceptor::APIFunctionArgument::create_u32     (in_planes),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLSWAPLAYERBUFFERS,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<WGL::PFNWGLSWAPLAYERBUFFERSPROC>(WGL::g_cached_swap_layer_buffers_func_ptr)(in_hdc,
                                                                                                              in_planes);
    }

    return result;
}

/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "Khronos/GL/glcorearb.h"
#include "Khronos/GL/wglext.h"
#include "WGL/globals.h"
#include "WGL/entrypoints/wgl_create_layer_context.h"

HGLRC WINAPI WGL::create_layer_context(HDC in_hdc,
                                       int in_layer_plane_index)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    HGLRC                                   result                 = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("wglCreateLayerContext(in_hdc=[%p] in_layer_plane_index=[%d])",
                 in_hdc,
                 in_layer_plane_index);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLCREATELAYERCONTEXT,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_void_ptr(in_hdc),
                APIInterceptor::APIFunctionArgument::create_i32     (in_layer_plane_index),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLCREATELAYERCONTEXT,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNWGLCREATELAYERCONTEXTPROC>(WGL::g_cached_create_layer_context_func_ptr)(in_hdc,
                                                                                                             in_layer_plane_index);
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLCREATELAYERCONTEXT,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const auto result_arg = APIInterceptor::APIFunctionArgument::create_void_ptr(result);

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLCREATELAYERCONTEXT,
                                   post_callback_func_arg,
                                  &result_arg);
        }
    }

    return result;
}

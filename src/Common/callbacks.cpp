/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <Windows.h>
#include "Common/callbacks.h"
#include "Common/types.h"
#include <vector>


typedef std::pair<APIInterceptor::PFNPOSTCALLBACKFUNCPROC, void*> PostAPIFuncCallback;
typedef std::pair<APIInterceptor::PFNPRECALLBACKFUNCPROC,  void*> PreAPIFuncCallback;

static auto         g_post_api_func_callback_vec = std::vector<PostAPIFuncCallback>(APIInterceptor::APIFUNCTION_COUNT);
static auto         g_pre_api_func_callback_vec  = std::vector<PreAPIFuncCallback> (APIInterceptor::APIFUNCTION_COUNT);
AI_THREADLOCAL bool g_callbacks_enabled          = true;

void APIInterceptor::disable_callbacks_for_this_thread()
{
    g_callbacks_enabled = false;
}

bool APIInterceptor::get_post_callback_for_function(const APIFunction&       in_api_func,
                                                    PFNPOSTCALLBACKFUNCPROC* out_callback_func_ptr,
                                                    void**                   out_user_arg_ptr)
{
    bool result = false;

    if (g_callbacks_enabled)
    {
        auto data_ptr = &g_post_api_func_callback_vec.at(static_cast<size_t>(in_api_func) );

        *out_callback_func_ptr = data_ptr->first;
        *out_user_arg_ptr      = data_ptr->second;

        result = (data_ptr->first != nullptr);
    }

    return result;
}

bool APIInterceptor::get_pre_callback_for_function(const APIFunction&                      in_api_func,
                                                   APIInterceptor::PFNPRECALLBACKFUNCPROC* out_callback_func_ptr,
                                                   void**                                  out_user_arg_ptr)
{
    bool result = false;

    if (g_callbacks_enabled)
    {
        auto data_ptr = &g_pre_api_func_callback_vec.at(static_cast<size_t>(in_api_func) );

        *out_callback_func_ptr = data_ptr->first;
        *out_user_arg_ptr      = data_ptr->second;

        result = (data_ptr->first != nullptr);
    }

    return result;
}

void APIInterceptor::register_for_post_callback(APIFunction                             in_function,
                                                APIInterceptor::PFNPOSTCALLBACKFUNCPROC in_callback_func_ptr,
                                                void*                                   in_func_user_arg)
{
    g_post_api_func_callback_vec[static_cast<uint32_t>(in_function)] = PostAPIFuncCallback{in_callback_func_ptr,
                                                                                           in_func_user_arg};
}

void APIInterceptor::register_for_pre_callback(APIFunction                            in_function,
                                               APIInterceptor::PFNPRECALLBACKFUNCPROC in_callback_func_ptr,
                                               void*                                  in_func_user_arg)
{
    g_pre_api_func_callback_vec[static_cast<uint32_t>(in_function)] = PreAPIFuncCallback{in_callback_func_ptr,
                                                                                         in_func_user_arg};
}


/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_CALLBACKS_H
#define COMMON_CALLBACKS_H

#include "types.h"

namespace APIInterceptor
{
    typedef void (*PFNCALLBACKFUNCPROC)(APIFunction                in_api_func,
                                        uint32_t                   in_n_args,
                                        const APIFunctionArgument* in_args_ptr,
                                        void*                      in_user_arg_ptr);

    void disable_callbacks_for_this_thread();
    bool get_callback_for_function        (const APIFunction&                  in_api_func,
                                           PFNCALLBACKFUNCPROC*                out_callback_func_ptr,
                                           void**                              out_user_arg_ptr);
    void register_for_callback            (APIFunction                         in_function,
                                           APIInterceptor::PFNCALLBACKFUNCPROC in_callback_func_ptr,
                                           void*                               in_func_user_arg);
}

#endif /* COMMON_CALLBACKS_H */
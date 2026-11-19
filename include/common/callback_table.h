/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_CALLBACK_TABLE_H
#define COMMON_CALLBACK_TABLE_H

#include "common/callbacks.h"
#include "common/globals.h"
#include "common/macros.h"

namespace APIInterceptor
{
    /* The callbacks that are called before and after the calls of each function: one slot per function, in plain arrays, so that a hooked call finds its callbacks with a few loads
     * and no function call. The arrays are written by CallbackRegistry while the process starts and are not changed after that. The hooks ask twice for every call (before it and
     * after it), and most functions have no callback after them, so this is on the path of every call of the application.
     */
    struct PostCallbackSlot
    {
        PFNPOSTCALLBACKFUNCPROC func_ptr     = nullptr;
        void*                   user_arg_ptr = nullptr;
    };

    struct PreCallbackSlot
    {
        PFNPRECALLBACKFUNCPROC func_ptr     = nullptr;
        void*                  user_arg_ptr = nullptr;
    };

    extern AI_THREADLOCAL bool g_are_callbacks_enabled; /* false for a thread that belongs to the interceptor (see disable_callbacks_for_this_thread()) */
    extern PostCallbackSlot    g_post_callback_slot_array[APIFUNCTION_COUNT];
    extern PreCallbackSlot     g_pre_callback_slot_array [APIFUNCTION_COUNT];

    /* Return false if the callbacks are disabled for the thread, or the function has none. */
    inline bool get_post_callback_for_function(const APIFunction&       in_api_func,
                                               PFNPOSTCALLBACKFUNCPROC* out_callback_func_ptr,
                                               void**                   out_user_arg_ptr)
    {
        bool result = false;

        AI_ASSERT(static_cast<size_t>(in_api_func) < static_cast<size_t>(APIFUNCTION_COUNT) );

        if (g_are_callbacks_enabled)
        {
            const PostCallbackSlot& slot = g_post_callback_slot_array[static_cast<size_t>(in_api_func)];

            *out_callback_func_ptr = slot.func_ptr;
            *out_user_arg_ptr      = slot.user_arg_ptr;

            result = (slot.func_ptr != nullptr);
        }

        return result;
    }

    inline bool get_pre_callback_for_function(const APIFunction&      in_api_func,
                                              PFNPRECALLBACKFUNCPROC* out_callback_func_ptr,
                                              void**                  out_user_arg_ptr)
    {
        bool result = false;

        AI_ASSERT(static_cast<size_t>(in_api_func) < static_cast<size_t>(APIFUNCTION_COUNT) );

        if (g_are_callbacks_enabled)
        {
            const PreCallbackSlot& slot = g_pre_callback_slot_array[static_cast<size_t>(in_api_func)];

            *out_callback_func_ptr = slot.func_ptr;
            *out_user_arg_ptr      = slot.user_arg_ptr;

            result = (slot.func_ptr != nullptr);
        }

        return result;
    }
}

#endif /* COMMON_CALLBACK_TABLE_H */

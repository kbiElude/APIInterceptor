/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The contents of the resources which a program writes through a lock, as arguments of the call that unlocks them.
 */
#ifndef HOOKS_COMMON_LOCK_CAPTURE_H
#define HOOKS_COMMON_LOCK_CAPTURE_H

#include "Common/types.h"
#include <cstdint>

namespace Interception
{
    namespace Hooks
    {
        namespace Common
        {
            /* The data of the region that is locked (see LockTracker), unless it was locked for reading only, as a data chunk.
             * An empty chunk if there is nothing to store.
             */
            APIInterceptor::APIFunctionArgument create_locked_data_argument(const void*     in_object_ptr,
                                                                            const uint32_t& in_level,
                                                                            const uint32_t& in_read_only_flag);
        }
    }
}

#endif /* HOOKS_COMMON_LOCK_CAPTURE_H */

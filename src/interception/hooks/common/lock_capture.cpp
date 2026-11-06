/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/hooks/common/argument_factory.h"
#include "interception/hooks/common/lock_capture.h"
#include "interception/hooks/common/lock_tracker.h"

APIInterceptor::APIFunctionArgument Interception::Hooks::Common::create_locked_data_argument(const void*     in_object_ptr,
                                                                                             const uint32_t& in_level,
                                                                                             const uint32_t& in_read_only_flag)
{
    LockRecord lock_record = {};
    bool       has_data    = LockTracker::get_ptr()->get_lock(in_object_ptr,
                                                              in_level,
                                                             &lock_record);

    /* Nothing was written to a resource which was locked for reading. */
    if (has_data                                    &&
        (lock_record.flags & in_read_only_flag) != 0)
    {
        has_data = false;
    }

    return ArgumentFactory::create_chunk(has_data ? lock_record.data_ptr
                                                  : nullptr,
                                         has_data ? lock_record.n_bytes
                                                  : 0);
}

/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Remembers the regions of resources which the application has locked, until it unlocks them. The contents are
 * captured at unlock time, when the application is done writing.
 */
#ifndef D3D8_LOCK_TRACKER_H
#define D3D8_LOCK_TRACKER_H

#include "D3D8/types.h"
#include <map>
#include <mutex>
#include <utility>

namespace D3D8
{
    class LockTracker
    {
    public:
        static LockTracker* get_ptr();

        /* Returns false if the object has no lock at the level (buffers and surfaces use level 0). */
        bool get_lock(const void*     in_object_ptr,
                      const uint32_t& in_level,
                      LockRecord*     out_lock_record_ptr);

        void on_locked  (const void*       in_object_ptr,
                         const uint32_t&   in_level,
                         const LockRecord& in_lock_record);
        void on_unlocked(const void*       in_object_ptr,
                         const uint32_t&   in_level);

    private:
        std::mutex                                             m_mutex;
        std::map<std::pair<const void*, uint32_t>, LockRecord> m_lock_record_map;
    };
}

#endif /* D3D8_LOCK_TRACKER_H */

/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "D3D8/lock_tracker.h"

D3D8::LockTracker* D3D8::LockTracker::get_ptr()
{
    static LockTracker instance;

    return &instance;
}

bool D3D8::LockTracker::get_lock(const void*     in_object_ptr,
                                 const uint32_t& in_level,
                                 LockRecord*     out_lock_record_ptr)
{
    bool result = false;

    {
        std::lock_guard<std::mutex> lock(m_mutex);

        const auto map_iterator = m_lock_record_map.find(std::make_pair(in_object_ptr,
                                                                        in_level) );

        if (map_iterator != m_lock_record_map.end() )
        {
            *out_lock_record_ptr = map_iterator->second;
            result               = true;
        }
    }

    return result;
}

void D3D8::LockTracker::on_locked(const void*       in_object_ptr,
                                  const uint32_t&   in_level,
                                  const LockRecord& in_lock_record)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        m_lock_record_map[std::make_pair(in_object_ptr,
                                         in_level)] = in_lock_record;
    }
}

void D3D8::LockTracker::on_unlocked(const void*     in_object_ptr,
                                    const uint32_t& in_level)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        m_lock_record_map.erase(std::make_pair(in_object_ptr,
                                               in_level) );
    }
}

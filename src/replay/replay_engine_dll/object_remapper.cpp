/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "object_remapper.h"

Replay::ReplayEngineDLL::ObjectRemapper::ObjectRemapper()
{
    /* Stub */
}

void Replay::ReplayEngineDLL::ObjectRemapper::add(const ObjectKind& in_kind,
                                                    const uint64_t&   in_dumped_value,
                                                    const uint64_t&   in_live_value)
{
    m_live_value_map[std::make_pair(in_kind,
                                    in_dumped_value)] = in_live_value;
}

void Replay::ReplayEngineDLL::ObjectRemapper::clear()
{
    m_live_value_map.clear();
}

bool Replay::ReplayEngineDLL::ObjectRemapper::get(const ObjectKind& in_kind,
                                                    const uint64_t&   in_dumped_value,
                                                    uint64_t*         out_live_value_ptr) const
{
    bool result = false;

    if (in_dumped_value == 0)
    {
        *out_live_value_ptr = 0;
        result              = true;

        goto end;
    }

    {
        const auto iterator = m_live_value_map.find(std::make_pair(in_kind,
                                                                   in_dumped_value) );

        if (iterator != m_live_value_map.end() )
        {
            *out_live_value_ptr = iterator->second;
            result              = true;
        }
    }

end:
    return result;
}

void Replay::ReplayEngineDLL::ObjectRemapper::remove(const ObjectKind& in_kind,
                                                       const uint64_t&   in_dumped_value)
{
    m_live_value_map.erase(std::make_pair(in_kind,
                                          in_dumped_value) );
}

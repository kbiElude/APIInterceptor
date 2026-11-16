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
    const auto forward_key = std::make_pair(in_kind,
                                            in_dumped_value);
    const auto iterator    = m_live_value_map.find(forward_key);

    /* What the dumped value stood for until now stops being found by it. */
    if (iterator != m_live_value_map.end() )
    {
        forget_dumped(in_kind,
                      in_dumped_value,
                      iterator->second);
    }

    m_live_value_map[forward_key] = in_live_value;

    m_dumped_value_set_by_live_map[std::make_pair(in_kind,
                                                  in_live_value)].insert(in_dumped_value);
}

void Replay::ReplayEngineDLL::ObjectRemapper::clear()
{
    m_dumped_value_set_by_live_map.clear();
    m_live_value_map.clear();
}

bool Replay::ReplayEngineDLL::ObjectRemapper::find_dumped(const ObjectKind& in_kind,
                                                       const uint64_t&   in_live_value,
                                                       uint64_t*         out_dumped_value_ptr) const
{
    bool       result   = false;
    const auto iterator = m_dumped_value_set_by_live_map.find(std::make_pair(in_kind,
                                                                             in_live_value) );

    /* The smallest of the dumped values, as the order of the map gave it. */
    if (iterator != m_dumped_value_set_by_live_map.end() )
    {
        *out_dumped_value_ptr = *iterator->second.begin();
        result                = true;
    }

    return result;
}

void Replay::ReplayEngineDLL::ObjectRemapper::forget_dumped(const ObjectKind& in_kind,
                                                            const uint64_t&   in_dumped_value,
                                                            const uint64_t&   in_live_value)
{
    const auto iterator = m_dumped_value_set_by_live_map.find(std::make_pair(in_kind,
                                                                             in_live_value) );

    if (iterator != m_dumped_value_set_by_live_map.end() )
    {
        iterator->second.erase(in_dumped_value);

        if (iterator->second.empty() )
        {
            m_dumped_value_set_by_live_map.erase(iterator);
        }
    }
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
    const auto iterator = m_live_value_map.find(std::make_pair(in_kind,
                                                               in_dumped_value) );

    if (iterator != m_live_value_map.end() )
    {
        forget_dumped(in_kind,
                      in_dumped_value,
                      iterator->second);

        m_live_value_map.erase(iterator);
    }
}

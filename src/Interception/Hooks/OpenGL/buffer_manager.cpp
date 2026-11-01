/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "Interception/Hooks/OpenGL/buffer_manager.h"

OpenGL::BufferManager::BufferManager()
    :m_bound_buffer_vec(static_cast<size_t>(BufferBindingTarget::COUNT),
                        0)
{
    /* Stub */
}

uint32_t OpenGL::BufferManager::get_bound_buffer(const BufferBindingTarget& in_target) const
{
    AI_ASSERT(static_cast<size_t>(in_target) < m_bound_buffer_vec.size() );

    return m_bound_buffer_vec.at(static_cast<size_t>(in_target) );
}

uint64_t OpenGL::BufferManager::get_size(const uint32_t& in_buffer) const
{
    const auto size_iterator = m_size_map.find(in_buffer);
    uint64_t   result        = 0;

    if (size_iterator != m_size_map.end() )
    {
        result = size_iterator->second;
    }

    return result;
}

void OpenGL::BufferManager::on_buffer_bound(const BufferBindingTarget& in_target,
                                            const uint32_t&            in_buffer)
{
    AI_ASSERT(static_cast<size_t>(in_target) < m_bound_buffer_vec.size() );

    m_bound_buffer_vec.at(static_cast<size_t>(in_target) ) = in_buffer;
}

void OpenGL::BufferManager::on_buffer_deleted(const uint32_t& in_buffer)
{
    m_size_map.erase(in_buffer);

    /* Deleting a bound buffer unbinds it. */
    for (auto& current_bound_buffer : m_bound_buffer_vec)
    {
        if (current_bound_buffer == in_buffer)
        {
            current_bound_buffer = 0;
        }
    }
}

void OpenGL::BufferManager::set_size(const uint32_t& in_buffer,
                                     const uint64_t& in_size)
{
    m_size_map[in_buffer] = in_size;
}

/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/macros.h"
#include "interception/hooks/OpenGL/buffer_mapping_manager.h"
#include "interception/hooks/OpenGL/types.h"

Interception::Hooks::OpenGL::BufferMappingManager::BufferMappingManager()
{
    /* Stub */
}

uint32_t Interception::Hooks::OpenGL::BufferMappingManager::get_flags_for_access(const uint32_t& in_access)
{
    uint32_t result = 0;

    switch (in_access)
    {
        case GL_READ_ONLY:  result = GL_MAP_READ_BIT;                    break;
        case GL_READ_WRITE: result = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT; break;
        case GL_WRITE_ONLY: result = GL_MAP_WRITE_BIT;                   break;

        default:
        {
            AI_FAIL_UNSUPPORTED(in_access);
        }
    }

    return result;
}

Interception::Hooks::OpenGL::BufferMappingManager::Region Interception::Hooks::OpenGL::BufferMappingManager::get_flush_region(const uint32_t& in_buffer,
                                                                                                                              const int64_t&  in_offset,
                                                                                                                              const int64_t&  in_length) const
{
    const auto mapping_ptr = get_mapping_ptr(in_buffer);
    Region     result;

    if (mapping_ptr == nullptr)
    {
        goto end;
    }

    if ( (mapping_ptr->flags & GL_MAP_FLUSH_EXPLICIT_BIT) == 0)
    {
        goto end;
    }

    if ( (mapping_ptr->flags & GL_MAP_WRITE_BIT) == 0)
    {
        goto end;
    }

    /* The range has to be inside the mapping. */
    if (in_offset < 0                              ||
        in_length <= 0                             ||
        in_offset + in_length > mapping_ptr->length)
    {
        AI_ASSERT_FAIL();

        goto end;
    }

    result.data_ptr = static_cast<const uint8_t*>(mapping_ptr->mapped_ptr) + in_offset;
    result.n_bytes  = static_cast<uint64_t>(in_length);
end:
    return result;
}

Interception::Hooks::OpenGL::BufferMappingManager::Region Interception::Hooks::OpenGL::BufferMappingManager::get_initial_region(const uint32_t& in_buffer) const
{
    const auto mapping_ptr = get_mapping_ptr(in_buffer);
    Region     result;

    if (mapping_ptr == nullptr)
    {
        goto end;
    }

    if ( (mapping_ptr->flags & GL_MAP_READ_BIT) == 0)
    {
        goto end;
    }

    /* What an invalidating mapping covers is undefined. */
    if ( (mapping_ptr->flags & (GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_INVALIDATE_RANGE_BIT) ) != 0)
    {
        goto end;
    }

    result.data_ptr = mapping_ptr->mapped_ptr;
    result.n_bytes  = static_cast<uint64_t>(mapping_ptr->length);
end:
    return result;
}

const Interception::Hooks::OpenGL::BufferMappingManager::Mapping* Interception::Hooks::OpenGL::BufferMappingManager::get_mapping_ptr(const uint32_t& in_buffer) const
{
    const auto     mapping_iterator = m_mapping_map.find(in_buffer);
    const Mapping* result_ptr       = nullptr;

    if (mapping_iterator != m_mapping_map.end() )
    {
        result_ptr = &mapping_iterator->second;
    }

    return result_ptr;
}

Interception::Hooks::OpenGL::BufferMappingManager::Region Interception::Hooks::OpenGL::BufferMappingManager::get_unmap_region(const uint32_t& in_buffer) const
{
    const auto mapping_ptr = get_mapping_ptr(in_buffer);
    Region     result;

    if (mapping_ptr == nullptr)
    {
        goto end;
    }

    if ( (mapping_ptr->flags & GL_MAP_WRITE_BIT) == 0)
    {
        goto end;
    }

    /* Flushed ranges were handed over by the flush calls. */
    if ( (mapping_ptr->flags & GL_MAP_FLUSH_EXPLICIT_BIT) != 0)
    {
        goto end;
    }

    result.data_ptr = mapping_ptr->mapped_ptr;
    result.n_bytes  = static_cast<uint64_t>(mapping_ptr->length);
end:
    return result;
}

bool Interception::Hooks::OpenGL::BufferMappingManager::is_mapped(const uint32_t& in_buffer) const
{
    return (get_mapping_ptr(in_buffer) != nullptr);
}

bool Interception::Hooks::OpenGL::BufferMappingManager::is_persistent(const uint32_t& in_buffer) const
{
    const auto mapping_ptr = get_mapping_ptr(in_buffer);
    bool       result      = false;

    if (mapping_ptr != nullptr)
    {
        result = ( (mapping_ptr->flags & GL_MAP_PERSISTENT_BIT) != 0);
    }

    return result;
}

void Interception::Hooks::OpenGL::BufferMappingManager::on_buffer_deleted(const uint32_t& in_buffer)
{
    m_mapping_map.erase(in_buffer);
}

void Interception::Hooks::OpenGL::BufferMappingManager::on_buffer_mapped(const uint32_t& in_buffer,
                                                                         void*           in_mapped_ptr,
                                                                         const int64_t&  in_offset,
                                                                         const int64_t&  in_length,
                                                                         const uint32_t& in_flags)
{
    if (in_mapped_ptr != nullptr)
    {
        auto& mapping = m_mapping_map[in_buffer];

        mapping.flags      = in_flags;
        mapping.length     = in_length;
        mapping.mapped_ptr = in_mapped_ptr;
        mapping.offset     = in_offset;
    }
}

void Interception::Hooks::OpenGL::BufferMappingManager::on_buffer_unmapped(const uint32_t& in_buffer)
{
    m_mapping_map.erase(in_buffer);
}

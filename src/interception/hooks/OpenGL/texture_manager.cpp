/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/macros.h"
#include "interception/hooks/OpenGL/texture_manager.h"

/* Levels are numbered with 16 bits. */
static constexpr uint32_t N_LEVEL_KEY_BITS = 16;

Interception::Hooks::OpenGL::TextureManager::TextureManager()
    :m_bound_texture_vec(static_cast<size_t>(TextureBindingTarget::COUNT),
                         0)
{
    /* Stub */
}

uint32_t Interception::Hooks::OpenGL::TextureManager::get_bound_texture(const TextureBindingTarget& in_target) const
{
    AI_ASSERT(static_cast<size_t>(in_target) < m_bound_texture_vec.size() );

    return m_bound_texture_vec.at(static_cast<size_t>(in_target) );
}

uint64_t Interception::Hooks::OpenGL::TextureManager::get_level_key(const uint32_t& in_texture,
                                                                    const int32_t&  in_level)
{
    return (static_cast<uint64_t>(in_texture) << N_LEVEL_KEY_BITS) |
           (static_cast<uint64_t>(in_level)   & ((1ull << N_LEVEL_KEY_BITS) - 1) );
}

Interception::Hooks::OpenGL::TextureManager::LevelProps Interception::Hooks::OpenGL::TextureManager::get_level_props(const uint32_t& in_texture,
                                                                                                                     const int32_t&  in_level) const
{
    const auto props_iterator = m_level_props_map.find(get_level_key(in_texture,
                                                                     in_level) );
    LevelProps result;

    if (props_iterator != m_level_props_map.end() )
    {
        result = props_iterator->second;
    }

    return result;
}

void Interception::Hooks::OpenGL::TextureManager::on_texture_bound(const TextureBindingTarget& in_target,
                                                                   const uint32_t&             in_texture)
{
    AI_ASSERT(static_cast<size_t>(in_target) < m_bound_texture_vec.size() );

    m_bound_texture_vec.at(static_cast<size_t>(in_target) ) = in_texture;
}

void Interception::Hooks::OpenGL::TextureManager::on_texture_deleted(const uint32_t& in_texture)
{
    /* All the levels of the texture, which are next to one another. */
    const auto first_iterator = m_level_props_map.lower_bound(get_level_key(in_texture,
                                                                            0) );
    const auto last_iterator  = m_level_props_map.lower_bound(get_level_key(in_texture + 1,
                                                                            0) );

    m_level_props_map.erase(first_iterator,
                            last_iterator);

    /* Deleting a bound texture unbinds it. */
    for (auto& current_bound_texture : m_bound_texture_vec)
    {
        if (current_bound_texture == in_texture)
        {
            current_bound_texture = 0;
        }
    }
}

void Interception::Hooks::OpenGL::TextureManager::set_compressed_level_props(const uint32_t& in_texture,
                                                                             const int32_t&  in_level,
                                                                             const uint32_t& in_compressed_size_bytes,
                                                                             const uint32_t& in_width,
                                                                             const uint32_t& in_height,
                                                                             const uint32_t& in_depth)
{
    LevelProps props;

    props.compressed_size_bytes = in_compressed_size_bytes;
    props.depth                 = in_depth;
    props.height                = in_height;
    props.width                 = in_width;

    m_level_props_map[get_level_key(in_texture,
                                    in_level)] = props;
}

void Interception::Hooks::OpenGL::TextureManager::set_level_props(const uint32_t& in_texture,
                                                                  const int32_t&  in_level,
                                                                  const uint32_t& in_width,
                                                                  const uint32_t& in_height,
                                                                  const uint32_t& in_depth)
{
    set_compressed_level_props(in_texture,
                               in_level,
                               0, /* in_compressed_size_bytes */
                               in_width,
                               in_height,
                               in_depth);
}

/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(OPENGL_TEXTURE_MANAGER_H)
#define OPENGL_TEXTURE_MANAGER_H

#include "OpenGL/types_enums.h"
#include <cstdint>
#include <map>
#include <vector>

namespace OpenGL
{
    /* Tracks which texture objects are bound to the binding points of a GL context, and what the levels of the texture
     * objects look like. There is one for each GL context (see ContextState).
     */
    class TextureManager
    {
    public:
        /* What the app specified for a level of a texture. All zeroes if it did not. */
        struct LevelProps
        {
            uint32_t compressed_size_bytes = 0;
            uint32_t depth                 = 0;
            uint32_t height                = 0;
            uint32_t width                 = 0;
        };

        TextureManager();

        /* Returns 0 if no texture is bound. */
        uint32_t get_bound_texture(const TextureBindingTarget& in_target) const;

        LevelProps get_level_props   (const uint32_t&             in_texture,
                                      const int32_t&              in_level) const;
        void       on_texture_bound  (const TextureBindingTarget& in_target,
                                      const uint32_t&             in_texture);
        void       on_texture_deleted(const uint32_t&             in_texture);

        /* As set_level_props(), for a level that holds compressed data. */
        void set_compressed_level_props(const uint32_t& in_texture,
                                        const int32_t&  in_level,
                                        const uint32_t& in_compressed_size_bytes,
                                        const uint32_t& in_width,
                                        const uint32_t& in_height,
                                        const uint32_t& in_depth);

        /* Replaces everything known about the level. */
        void set_level_props(const uint32_t& in_texture,
                             const int32_t&  in_level,
                             const uint32_t& in_width,
                             const uint32_t& in_height,
                             const uint32_t& in_depth);

    private:
        /* The texture and the level are packed into one key, so that the levels of a texture are next to one another. */
        static uint64_t get_level_key(const uint32_t& in_texture,
                                      const int32_t&  in_level);

        std::vector<uint32_t>          m_bound_texture_vec; /* indexed by TextureBindingTarget */
        std::map<uint64_t, LevelProps> m_level_props_map;
    };
}

#endif /* OPENGL_TEXTURE_MANAGER_H */

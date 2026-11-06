/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(OPENGL_BUFFER_MAPPING_MANAGER_H)
#define OPENGL_BUFFER_MAPPING_MANAGER_H

#include <cstdint>
#include <unordered_map>

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            /* Tracks the buffer objects which the app has mapped, and tells which memory it may have written to. There is one
             * for each GL context (see ContextState).
             *
             * What is recorded for the writes through a mapping:
             *  - If the mapping was created without GL_MAP_FLUSH_EXPLICIT_BIT, the whole mapped range is copied when the buffer
             *    is unmapped.
             *  - If it was created with GL_MAP_FLUSH_EXPLICIT_BIT, only the ranges that the app flushes are copied, when it
             *    flushes them; unmapping copies nothing.
             *  - Writes to a persistent mapping (GL_MAP_PERSISTENT_BIT) that happen between those moments are not seen.
             */
            class BufferMappingManager
            {
            public:
                /* A range of the app's memory which a call hands over to the GPU, or receives from it. */
                struct Region
                {
                    const void* data_ptr = nullptr;
                    uint64_t    n_bytes  = 0;
                };

                BufferMappingManager();

                /* The range (offset relative to the start of the mapping) which a flush call makes available to the GPU. Empty
                 * unless the mapping is writable and flushed explicitly.
                 */
                Region get_flush_region(const uint32_t& in_buffer,
                                        const int64_t&  in_offset,
                                        const int64_t&  in_length) const;

                /* The contents which the app finds in a new mapping. Empty unless the mapping is readable, and does not
                 * invalidate what it covers.
                 */
                Region get_initial_region(const uint32_t& in_buffer) const;

                /* The range which the app may have written to, and which unmapping hands over to the GPU. */
                Region get_unmap_region(const uint32_t& in_buffer) const;

                bool is_mapped        (const uint32_t& in_buffer) const;
                bool is_persistent    (const uint32_t& in_buffer) const;
                void on_buffer_deleted(const uint32_t& in_buffer);

                /* Does nothing if the map call failed (null pointer). */
                void on_buffer_mapped(const uint32_t& in_buffer,
                                      void*           in_mapped_ptr,
                                      const int64_t&  in_offset,
                                      const int64_t&  in_length,
                                      const uint32_t& in_flags);

                void on_buffer_unmapped(const uint32_t& in_buffer);

                /* The GL_MAP_*_BIT flags which the access token of glMapBuffer() stands for. */
                static uint32_t get_flags_for_access(const uint32_t& in_access);

            private:
                struct Mapping
                {
                    uint32_t flags      = 0; /* GL_MAP_*_BIT */
                    int64_t  length     = 0;
                    void*    mapped_ptr = nullptr;
                    int64_t  offset     = 0;
                };

                /* Returns null if the buffer is not mapped. */
                const Mapping* get_mapping_ptr(const uint32_t& in_buffer) const;

                std::unordered_map<uint32_t, Mapping> m_mapping_map;
            };
        }
    }
}

#endif /* OPENGL_BUFFER_MAPPING_MANAGER_H */

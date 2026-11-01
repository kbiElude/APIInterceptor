/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(OPENGL_BUFFER_MANAGER_H)
#define OPENGL_BUFFER_MANAGER_H

#include "Interception/Hooks/OpenGL/types_enums.h"
#include <cstdint>
#include <unordered_map>
#include <vector>

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            /* Tracks which buffer objects are bound to the binding points of a GL context, and how big the buffer objects are.
             * There is one for each GL context (see ContextState).
             */
            class BufferManager
            {
            public:
                BufferManager();

                /* Returns 0 if no buffer is bound. */
                uint32_t get_bound_buffer(const BufferBindingTarget& in_target) const;

                /* Size in bytes of the buffer's data store, as last specified by the app; 0 if not known. */
                uint64_t get_size(const uint32_t& in_buffer) const;

                void on_buffer_bound  (const BufferBindingTarget& in_target,
                                       const uint32_t&            in_buffer);
                void on_buffer_deleted(const uint32_t&            in_buffer);
                void set_size         (const uint32_t&            in_buffer,
                                       const uint64_t&            in_size);

            private:
                std::vector<uint32_t>                 m_bound_buffer_vec; /* indexed by BufferBindingTarget */
                std::unordered_map<uint32_t, uint64_t> m_size_map;
            };
        }
    }
}

#endif /* OPENGL_BUFFER_MANAGER_H */

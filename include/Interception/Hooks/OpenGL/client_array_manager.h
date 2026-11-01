/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(OPENGL_CLIENT_ARRAY_MANAGER_H)
#define OPENGL_CLIENT_ARRAY_MANAGER_H

#include "Interception/Hooks/OpenGL/types_enums.h"
#include <cstdint>
#include <map>
#include <utility>
#include <vector>

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            /* Tracks the vertex arrays which the app points at its own memory (as opposed to a buffer object), so that their
             * contents can be recorded when a draw call reads them.
             *
             * Only the default vertex array object is tracked: while another one is bound, the state changes are ignored, and
             * nothing is snapshotted.
             *
             * Layout of a snapshot (all fields are little-endian):
             *
             *   uint32_t n_arrays
             *   n_arrays x
             *   {
             *       uint32_t kind          ClientArrayKind
             *       uint32_t index         texture unit (tex coord arrays) or attribute index (generic arrays); 0 otherwise
             *       int32_t  size          as passed to the *Pointer call
             *       uint32_t type          GL type of a component
             *       uint32_t stride        as passed to the *Pointer call (0 = tightly packed)
             *       uint32_t flags         SNAPSHOT_FLAG_*
             *       uint32_t divisor
             *       uint64_t pointer       the app's pointer; a handle, not an address which can be dereferenced
             *       uint32_t first_element index of the first element which was copied
             *       uint32_t n_elements    number of elements which were copied
             *       uint32_t n_bytes       size of the copy, from the start of first_element to the end of the last element
             *       uint8_t  data[n_bytes]
             *   }
             */
            class ClientArrayManager
            {
            public:
                static constexpr uint32_t SNAPSHOT_FLAG_IS_INTEGER    = 1 << 0;
                static constexpr uint32_t SNAPSHOT_FLAG_IS_LONG       = 1 << 1;
                static constexpr uint32_t SNAPSHOT_FLAG_IS_NORMALIZED = 1 << 2;

                ClientArrayManager();

                uint32_t get_bound_vertex_array() const;

                /* Returns the texture unit (0-based) which glClientActiveTexture() selected. */
                uint32_t get_client_active_texture() const;

                /* Tells whether any enabled array reads the app's memory. */
                bool has_client_arrays() const;

                void set_bound_vertex_array   (const uint32_t&        in_vertex_array);
                void set_client_active_texture(const uint32_t&        in_texture_unit);
                void set_divisor              (const uint32_t&        in_index,
                                               const uint32_t&        in_divisor);
                void set_enabled              (const ClientArrayKind& in_kind,
                                               const uint32_t&        in_index,
                                               const bool&            in_is_enabled);
                void set_interleaved_arrays   (const uint32_t&        in_format,
                                               const int32_t&         in_stride,
                                               const void*            in_pointer_ptr,
                                               const uint32_t&        in_array_buffer);
                void set_pointer              (const ClientArrayKind& in_kind,
                                               const uint32_t&        in_index,
                                               const int32_t&         in_size,
                                               const uint32_t&        in_type,
                                               const int32_t&         in_stride,
                                               const void*            in_pointer_ptr,
                                               const uint32_t&        in_array_buffer,
                                               const bool&            in_is_integer,
                                               const bool&            in_is_long,
                                               const bool&            in_is_normalized);

                /* Copies the elements of the enabled client arrays which a draw call reads. The call reads in_n_elements
                 * elements starting at in_first_element, in each instance; arrays with a divisor are read by instance instead.
                 * Returns an empty vector if there is nothing to copy.
                 */
                std::vector<uint8_t> take_snapshot(const int64_t&  in_first_element,
                                                   const int64_t&  in_n_elements,
                                                   const uint32_t& in_instance_count,
                                                   const uint32_t& in_base_instance) const;

                /* Returns false if the token does not name a vertex array. */
                static bool get_kind_for_array_enum(const uint32_t&  in_array,
                                                    ClientArrayKind* out_kind_ptr);

            private:
                struct ClientArray
                {
                    uint32_t    array_buffer  = 0; /* bound when the pointer was set; 0 = the pointer is the app's memory */
                    uint32_t    divisor       = 0;
                    bool        is_enabled    = false;
                    bool        is_integer    = false;
                    bool        is_long       = false;
                    bool        is_normalized = false;
                    const void* pointer_ptr   = nullptr;
                    int32_t     size          = 4;
                    int32_t     stride        = 0;
                    uint32_t    type          = 0;
                };

                typedef std::pair<ClientArrayKind, uint32_t> ClientArrayKey;

                struct InterleavedFormat
                {
                    uint32_t color_size;
                    uint32_t color_type;
                    uint32_t format;
                    bool     has_normal;
                    uint32_t texture_size;
                    uint32_t vertex_size;
                };

                ClientArray& get_array(const ClientArrayKind& in_kind,
                                       const uint32_t&        in_index);

                /* Size of an element, in bytes, ignoring the stride. */
                static uint32_t get_element_n_bytes(const int32_t&  in_size,
                                                    const uint32_t& in_type);

                /* Returns null if the format is not one of the interleaved formats. */
                static const InterleavedFormat* get_interleaved_format_ptr(const uint32_t& in_format);

                static uint32_t get_n_type_bytes(const uint32_t& in_type);

                /* Tells whether the array reads the app's memory. */
                static bool is_client_array(const ClientArray& in_array);

                std::map<ClientArrayKey, ClientArray> m_array_map;
                uint32_t                              m_bound_vertex_array;
                uint32_t                              m_client_active_texture;
            };
        }
    }
}

#endif /* OPENGL_CLIENT_ARRAY_MANAGER_H */

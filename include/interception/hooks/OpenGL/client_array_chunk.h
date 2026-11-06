/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(OPENGL_CLIENT_ARRAY_CHUNK_H)
#define OPENGL_CLIENT_ARRAY_CHUNK_H

#include "common/callbacks.h"
#include <vector>

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            /* Takes a snapshot of the vertex arrays which a draw call reads from the app's memory (see ClientArrayManager for the
             * layout), and of the indices of an indexed draw call. As with StringChunk, the copies are made when the ID is
             * asked for for the first time, and only then, so nothing is copied unless a callback wants the arguments.
             *
             * The draw call tells what it reads by the add_*() calls, and by set_instancing(). The snapshot covers the range
             * of vertices which the draw call touches, as a whole: any vertices in between are copied, too.
             *
             * A vertex with the largest value of the index type is taken for a primitive restart index, and is not read.
             */
            class ClientArrayChunk
            {
            public:
                ClientArrayChunk();

                /* glDrawArrays() and the like. */
                void add_arrays(const int32_t& in_first,
                                const int32_t& in_count);

                /* glDrawElements() and the like. The indices are the app's, or an offset in the element array buffer. */
                void add_elements(const int32_t&  in_count,
                                  const uint32_t& in_type,
                                  const void*     in_indices_ptr,
                                  const int32_t&  in_base_vertex);

                /* glMultiDrawArrays(). */
                void add_multi_arrays(const int32_t* in_first_ptr,
                                      const int32_t* in_count_ptr,
                                      const int32_t& in_draw_count);

                /* glMultiDrawElements(). The array of base vertices may be null. */
                void add_multi_elements(const int32_t*     in_count_ptr,
                                        const uint32_t&    in_type,
                                        const void* const* in_indices_ptr_ptr,
                                        const int32_t&     in_draw_count,
                                        const int32_t*     in_base_vertex_ptr);

                /* The snapshot of the vertex arrays. Empty if no vertex array reads the app's memory. */
                APIInterceptor::DataChunkID get_id();

                /* The argument which stands for the indices of the (first) indexed draw: the offset, if the indices are in a
                 * buffer, or the ID of a chunk with a copy of the indices.
                 */
                APIInterceptor::APIFunctionArgument get_indices_arg();

                /* The argument which stands for the indices of glMultiDrawElements*(): a chunk with, for each draw, the offset
                 * (uint64_t) of its indices in the element array buffer, or the ID (uint32_t) of a chunk with a copy of them.
                 */
                APIInterceptor::APIFunctionArgument get_multi_indices_arg();

                void set_instancing(const int32_t&  in_instance_count,
                                    const uint32_t& in_base_instance);

            private:
                struct Request
                {
                    int32_t     base_vertex  = 0;
                    int32_t     count        = 0;
                    int32_t     first        = 0;
                    const void* indices_ptr  = nullptr;
                    bool        is_elements  = false;
                    uint32_t    type         = 0;
                };

                /* Returns false if the range could not be worked out. */
                static bool get_index_range(const Request& in_request,
                                            int64_t*       out_min_ptr,
                                            int64_t*       out_max_ptr);

                static uint32_t get_n_index_bytes(const uint32_t& in_type);

                uint32_t                            m_base_instance;
                APIInterceptor::DataChunkID         m_id;
                APIInterceptor::APIFunctionArgument m_indices_arg;
                uint32_t                            m_instance_count;
                bool                                m_is_indices_arg_ready;
                bool                                m_is_multi_indices_arg_ready;
                bool                                m_is_registered;
                APIInterceptor::APIFunctionArgument m_multi_indices_arg;
                std::vector<Request>                m_request_vec;
            };
        }
    }
}

#endif /* OPENGL_CLIENT_ARRAY_CHUNK_H */

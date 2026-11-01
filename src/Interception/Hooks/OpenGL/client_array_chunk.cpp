/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "Interception/Hooks/OpenGL/client_array_chunk.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Hooks/OpenGL/state_tracker.h"
#include "Interception/Hooks/WGL/globals.h"

Interception::Hooks::OpenGL::ClientArrayChunk::ClientArrayChunk()
    :m_base_instance       (0),
     m_id                  (0),
     m_instance_count      (1),
     m_is_indices_arg_ready      (false),
     m_is_multi_indices_arg_ready(false),
     m_is_registered             (false)
{
    /* Stub */
}

void Interception::Hooks::OpenGL::ClientArrayChunk::add_arrays(const int32_t& in_first,
                                                               const int32_t& in_count)
{
    Request request;

    request.count = in_count;
    request.first = in_first;

    m_request_vec.push_back(request);
}

void Interception::Hooks::OpenGL::ClientArrayChunk::add_elements(const int32_t&  in_count,
                                                                 const uint32_t& in_type,
                                                                 const void*     in_indices_ptr,
                                                                 const int32_t&  in_base_vertex)
{
    Request request;

    request.base_vertex = in_base_vertex;
    request.count       = in_count;
    request.indices_ptr = in_indices_ptr;
    request.is_elements = true;
    request.type        = in_type;

    m_request_vec.push_back(request);
}

void Interception::Hooks::OpenGL::ClientArrayChunk::add_multi_arrays(const int32_t* in_first_ptr,
                                                                     const int32_t* in_count_ptr,
                                                                     const int32_t& in_draw_count)
{
    if (in_first_ptr == nullptr)
    {
        goto end;
    }

    if (in_count_ptr == nullptr)
    {
        goto end;
    }

    for (int32_t n_draw = 0;
                 n_draw < in_draw_count;
               ++n_draw)
    {
        add_arrays(in_first_ptr[n_draw],
                   in_count_ptr[n_draw]);
    }

end:
    ;
}

void Interception::Hooks::OpenGL::ClientArrayChunk::add_multi_elements(const int32_t*     in_count_ptr,
                                                                       const uint32_t&    in_type,
                                                                       const void* const* in_indices_ptr_ptr,
                                                                       const int32_t&     in_draw_count,
                                                                       const int32_t*     in_base_vertex_ptr)
{
    if (in_count_ptr == nullptr)
    {
        goto end;
    }

    if (in_indices_ptr_ptr == nullptr)
    {
        goto end;
    }

    for (int32_t n_draw = 0;
                 n_draw < in_draw_count;
               ++n_draw)
    {
        add_elements(in_count_ptr[n_draw],
                     in_type,
                     in_indices_ptr_ptr[n_draw],
                     (in_base_vertex_ptr != nullptr) ? in_base_vertex_ptr[n_draw] : 0);
    }

end:
    ;
}

APIInterceptor::DataChunkID Interception::Hooks::OpenGL::ClientArrayChunk::get_id()
{
    if (m_is_registered == false)
    {
        std::vector<uint8_t> snapshot_u8_vec;
        auto&                state = Interception::Hooks::OpenGL::get_context_state().client_array_manager;

        if (state.has_client_arrays() )
        {
            int64_t first_element = INT64_MAX;
            int64_t last_element  = INT64_MIN;

            for (const auto& current_request : m_request_vec)
            {
                int64_t request_first = current_request.first;
                int64_t request_last  = static_cast<int64_t>(current_request.first) + current_request.count - 1;

                if (current_request.is_elements)
                {
                    int64_t min_index = 0;
                    int64_t max_index = 0;

                    if (get_index_range(current_request,
                                       &min_index,
                                       &max_index) == false)
                    {
                        continue;
                    }

                    request_first = min_index + current_request.base_vertex;
                    request_last  = max_index + current_request.base_vertex;
                }
                else
                if (current_request.count <= 0)
                {
                    continue;
                }

                if (request_first < first_element)
                {
                    first_element = request_first;
                }

                if (request_last > last_element)
                {
                    last_element = request_last;
                }
            }

            if (first_element <= last_element)
            {
                snapshot_u8_vec = state.take_snapshot(first_element,
                                                      last_element - first_element + 1,
                                                      m_instance_count,
                                                      m_base_instance);
            }
        }

        m_id            = APIInterceptor::register_data_chunk(snapshot_u8_vec.data(),
                                                              static_cast<uint32_t>(snapshot_u8_vec.size() ) );
        m_is_registered = true;
    }

    return m_id;
}

bool Interception::Hooks::OpenGL::ClientArrayChunk::get_index_range(const Request& in_request,
                                                                    int64_t*       out_min_ptr,
                                                                    int64_t*       out_max_ptr)
{
    std::vector<uint8_t> buffer_u8_vec;
    const uint8_t*       data_u8_ptr          = nullptr;
    const auto           element_array_buffer = Interception::Hooks::OpenGL::get_context_state().buffer_manager.get_bound_buffer(Interception::Hooks::OpenGL::BufferBindingTarget::ELEMENT_ARRAY_BUFFER);
    int64_t              max_index            = -1;
    int64_t              min_index            = INT64_MAX;
    const uint32_t       n_index_bytes        = get_n_index_bytes(in_request.type);
    bool                 result               = false;
    uint32_t             restart_index        = 0;

    if (n_index_bytes == 0)
    {
        goto end;
    }

    if (in_request.count <= 0)
    {
        goto end;
    }

    restart_index = (n_index_bytes == sizeof(uint32_t) ) ? UINT32_MAX
                                                         : ((1u << (n_index_bytes * 8) ) - 1);

    if (in_request.indices_ptr == nullptr)
    {
        if (element_array_buffer == 0)
        {
            goto end;
        }
    }

    if (element_array_buffer != 0)
    {
        /* The indices are in the buffer, which has to be read back. Buffers that are mapped cannot be. */
        const auto& context      = Interception::Hooks::OpenGL::get_context_state();
        void*       get_func_ptr = Interception::Hooks::OpenGL::g_cached_gl_get_buffer_sub_data;

        if (context.buffer_mapping_manager.is_mapped(element_array_buffer) )
        {
            goto end;
        }

        if (get_func_ptr == nullptr)
        {
            get_func_ptr = reinterpret_cast<void*>(reinterpret_cast<Interception::Hooks::WGL::PFNWGLGETPROCADDRESSPROC>(Interception::Hooks::WGL::g_cached_get_proc_address_func_ptr)("glGetBufferSubData") );
        }

        if (get_func_ptr == nullptr)
        {
            goto end;
        }

        buffer_u8_vec.resize(static_cast<size_t>(in_request.count) * n_index_bytes);

        reinterpret_cast<PFNGLGETBUFFERSUBDATAPROC>(get_func_ptr)(GL_ELEMENT_ARRAY_BUFFER,
                                                                  reinterpret_cast<GLintptr>(in_request.indices_ptr),
                                                                  static_cast<GLsizeiptr>(buffer_u8_vec.size() ),
                                                                  buffer_u8_vec.data() );

        data_u8_ptr = buffer_u8_vec.data();
    }
    else
    {
        data_u8_ptr = static_cast<const uint8_t*>(in_request.indices_ptr);
    }

    for (int32_t n_index = 0;
                 n_index < in_request.count;
               ++n_index)
    {
        uint32_t index = 0;

        switch (in_request.type)
        {
            case GL_UNSIGNED_BYTE:  index = data_u8_ptr[n_index];                                          break;
            case GL_UNSIGNED_SHORT: index = reinterpret_cast<const uint16_t*>(data_u8_ptr)[n_index];       break;
            case GL_UNSIGNED_INT:   index = reinterpret_cast<const uint32_t*>(data_u8_ptr)[n_index];       break;

            default:
            {
                AI_FAIL_UNSUPPORTED(in_request.type);
            }
        }

        /* See the class comment. */
        if (index == restart_index)
        {
            continue;
        }

        if (index < min_index)
        {
            min_index = index;
        }

        if (index > max_index)
        {
            max_index = index;
        }
    }

    if (max_index < 0)
    {
        goto end;
    }

    *out_max_ptr = max_index;
    *out_min_ptr = min_index;
    result       = true;
end:
    return result;
}

APIInterceptor::APIFunctionArgument Interception::Hooks::OpenGL::ClientArrayChunk::get_indices_arg()
{
    if (m_is_indices_arg_ready == false)
    {
        const auto element_array_buffer = Interception::Hooks::OpenGL::get_context_state().buffer_manager.get_bound_buffer(Interception::Hooks::OpenGL::BufferBindingTarget::ELEMENT_ARRAY_BUFFER);

        for (const auto& current_request : m_request_vec)
        {
            if (current_request.is_elements == false)
            {
                continue;
            }

            if (element_array_buffer != 0)
            {
                /* An offset in the buffer. */
                m_indices_arg = APIInterceptor::APIFunctionArgument::create_void_ptr(current_request.indices_ptr);
            }
            else
            {
                const uint32_t n_bytes = (current_request.indices_ptr != nullptr && current_request.count > 0) ? static_cast<uint32_t>(current_request.count) * get_n_index_bytes(current_request.type)
                                                                                                                : 0;

                m_indices_arg = APIInterceptor::APIFunctionArgument::create_data_chunk_id(APIInterceptor::register_data_chunk(current_request.indices_ptr,
                                                                                                                              n_bytes) );
            }

            break;
        }

        m_is_indices_arg_ready = true;
    }

    return m_indices_arg;
}

APIInterceptor::APIFunctionArgument Interception::Hooks::OpenGL::ClientArrayChunk::get_multi_indices_arg()
{
    if (m_is_multi_indices_arg_ready == false)
    {
        const auto element_array_buffer = Interception::Hooks::OpenGL::get_context_state().buffer_manager.get_bound_buffer(Interception::Hooks::OpenGL::BufferBindingTarget::ELEMENT_ARRAY_BUFFER);

        if (element_array_buffer != 0)
        {
            std::vector<uint64_t> offset_u64_vec;

            for (const auto& current_request : m_request_vec)
            {
                if (current_request.is_elements)
                {
                    offset_u64_vec.push_back(static_cast<uint64_t>(reinterpret_cast<uintptr_t>(current_request.indices_ptr) ) );
                }
            }

            m_multi_indices_arg = APIInterceptor::APIFunctionArgument::create_data_chunk_id(APIInterceptor::register_data_chunk(offset_u64_vec.data(),
                                                                                                                                static_cast<uint32_t>(offset_u64_vec.size() * sizeof(uint64_t) ) ) );
        }
        else
        {
            std::vector<APIInterceptor::DataChunkID> chunk_id_vec;

            for (const auto& current_request : m_request_vec)
            {
                if (current_request.is_elements)
                {
                    const uint32_t n_bytes = (current_request.indices_ptr != nullptr && current_request.count > 0) ? static_cast<uint32_t>(current_request.count) * get_n_index_bytes(current_request.type)
                                                                                                                    : 0;

                    chunk_id_vec.push_back(APIInterceptor::register_data_chunk(current_request.indices_ptr,
                                                                               n_bytes) );
                }
            }

            m_multi_indices_arg = APIInterceptor::APIFunctionArgument::create_data_chunk_id(APIInterceptor::register_data_chunk(chunk_id_vec.data(),
                                                                                                                                static_cast<uint32_t>(chunk_id_vec.size() * sizeof(APIInterceptor::DataChunkID) ) ) );
        }

        m_is_multi_indices_arg_ready = true;
    }

    return m_multi_indices_arg;
}

uint32_t Interception::Hooks::OpenGL::ClientArrayChunk::get_n_index_bytes(const uint32_t& in_type)
{
    uint32_t result = 0;

    switch (in_type)
    {
        case GL_UNSIGNED_BYTE:  result = sizeof(uint8_t);  break;
        case GL_UNSIGNED_INT:   result = sizeof(uint32_t); break;
        case GL_UNSIGNED_SHORT: result = sizeof(uint16_t); break;

        default:
        {
            AI_FAIL_UNSUPPORTED(in_type);
        }
    }

    return result;
}

void Interception::Hooks::OpenGL::ClientArrayChunk::set_instancing(const int32_t&  in_instance_count,
                                                                   const uint32_t& in_base_instance)
{
    m_base_instance  = in_base_instance;
    m_instance_count = (in_instance_count > 0) ? static_cast<uint32_t>(in_instance_count)
                                               : 0;
}

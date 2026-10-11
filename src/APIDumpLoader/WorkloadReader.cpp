/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "APIDumpLoader/WorkloadReader.h"
#include <algorithm>
#include <string.h>

/* Shared by several functions. An item bigger than MAX_ITEM_N_BYTES is a sign of corruption. */
static constexpr size_t   BUFFER_N_BYTES   = 1024 * 1024;
static constexpr uint32_t MAX_ITEM_N_BYTES = 1u << 30; /* 1 GiB */
static constexpr size_t   MAX_PEEK_N_BYTES = 64;

APIDumpLoader::WorkloadReader::WorkloadReader()
    :m_buffer_end        (0),
     m_buffer_start      (0),
     m_file_handle       (nullptr),
     m_is_finished       (false),
     m_is_truncated      (false),
     m_n_data_chunks_read(0)
{
    /* The padding keeps parsing code from reading outside the buffer when a file ends early. */
    m_buffer_u8_vec.resize(BUFFER_N_BYTES + MAX_PEEK_N_BYTES);
}

APIDumpLoader::WorkloadReader::~WorkloadReader()
{
    if (m_file_handle != nullptr)
    {
        ::fclose(m_file_handle);
    }
}

APIDumpLoader::WorkloadReaderUniquePtr APIDumpLoader::WorkloadReader::create(const char* in_filename_ptr)
{
    WorkloadReaderUniquePtr result_ptr(new WorkloadReader() );

    result_ptr->m_file_handle = ::fopen(in_filename_ptr,
                                        "rb");

    if (result_ptr->m_file_handle == nullptr)
    {
        result_ptr.reset();
    }

    return result_ptr;
}

bool APIDumpLoader::WorkloadReader::is_truncated() const
{
    return m_is_truncated;
}

size_t APIDumpLoader::WorkloadReader::peek(const size_t& in_n_bytes)
{
    if (m_buffer_end - m_buffer_start < in_n_bytes)
    {
        /* Move what is left to the front, and top the buffer up. */
        const size_t n_bytes_left = m_buffer_end - m_buffer_start;

        memmove(m_buffer_u8_vec.data(),
                m_buffer_u8_vec.data() + m_buffer_start,
                n_bytes_left);

        m_buffer_start = 0;
        m_buffer_end   = n_bytes_left;
        m_buffer_end  += ::fread(m_buffer_u8_vec.data() + m_buffer_end,
                                 1,
                                 BUFFER_N_BYTES - m_buffer_end,
                                 m_file_handle);

        memset(m_buffer_u8_vec.data() + m_buffer_end,
               0,
               MAX_PEEK_N_BYTES);
    }

    return m_buffer_end - m_buffer_start;
}

bool APIDumpLoader::WorkloadReader::read_api_call(DumpedAPICall* out_api_call_ptr)
{
    constexpr size_t   HEADER_N_BYTES           = sizeof(APIInterceptor::APIFunction) + 2 * sizeof(uint32_t); /* function, n in args, n out args */
    constexpr size_t   MAX_ARGUMENT_N_BYTES     = 16;                                                         /* type and the widest payload */
    constexpr uint32_t MAX_N_ARGUMENTS_PER_CALL = 64;

    const uint8_t*                      header_u8_ptr   = nullptr;
    uint32_t                            n_in_arguments  = 0;
    uint32_t                            n_out_arguments = 0;
    bool                                result          = false;
    APIInterceptor::APIFunctionArgument returned_value;

    /* Reads one argument. */
    const auto read_argument_func = [&](APIInterceptor::APIFunctionArgument* out_argument_ptr)
    {
        const size_t n_bytes_available = peek(MAX_ARGUMENT_N_BYTES);
        uint32_t     n_bytes_used      = 0;
        bool         is_ok             = false;

        if (n_bytes_available != 0)
        {
            n_bytes_used = out_argument_ptr->deserialize_from_u8_ptr(m_buffer_u8_vec.data() + m_buffer_start);

            if (n_bytes_used <= n_bytes_available)
            {
                m_buffer_start += n_bytes_used;
                is_ok           = true;
            }
        }

        return is_ok;
    };

    if (peek(HEADER_N_BYTES) < HEADER_N_BYTES)
    {
        goto end;
    }

    header_u8_ptr = m_buffer_u8_vec.data() + m_buffer_start;

    memcpy(&out_api_call_ptr->func,
           header_u8_ptr,
           sizeof(APIInterceptor::APIFunction) );
    memcpy(&n_in_arguments,
           header_u8_ptr + sizeof(APIInterceptor::APIFunction),
           sizeof(uint32_t) );
    memcpy(&n_out_arguments,
           header_u8_ptr + sizeof(APIInterceptor::APIFunction) + sizeof(uint32_t),
           sizeof(uint32_t) );

    m_buffer_start += HEADER_N_BYTES;

    if (n_in_arguments > MAX_N_ARGUMENTS_PER_CALL)
    {
        goto end;
    }

    if (n_out_arguments > MAX_N_ARGUMENTS_PER_CALL)
    {
        goto end;
    }

    out_api_call_ptr->arg_in_vec.resize (n_in_arguments);
    out_api_call_ptr->arg_out_vec.resize(n_out_arguments);

    for (auto& current_argument : out_api_call_ptr->arg_in_vec)
    {
        if (read_argument_func(&current_argument) == false)
        {
            goto end;
        }
    }

    for (auto& current_argument : out_api_call_ptr->arg_out_vec)
    {
        if (read_argument_func(&current_argument) == false)
        {
            goto end;
        }
    }

    if (read_argument_func(&returned_value) == false)
    {
        goto end;
    }

    if (returned_value.type != APIInterceptor::APIFunctionArgumentType::UNKNOWN)
    {
        out_api_call_ptr->returned_value_ptr.reset(
            new APIInterceptor::APIFunctionArgument(returned_value)
        );
    }

    result = true;
end:
    return result;
}

bool APIDumpLoader::WorkloadReader::read_bytes(void*         out_data_ptr,
                                               const size_t& in_n_bytes)
{
    const size_t n_bytes_buffered = std::min<size_t>(in_n_bytes,
                                                     m_buffer_end - m_buffer_start);
    size_t       n_bytes_read     = n_bytes_buffered;

    if (n_bytes_buffered != 0)
    {
        memcpy(out_data_ptr,
               m_buffer_u8_vec.data() + m_buffer_start,
               n_bytes_buffered);

        m_buffer_start += n_bytes_buffered;
    }

    /* The rest does not go through the buffer. */
    if (n_bytes_read < in_n_bytes)
    {
        n_bytes_read += ::fread(static_cast<uint8_t*>(out_data_ptr) + n_bytes_read,
                                1,
                                in_n_bytes - n_bytes_read,
                                m_file_handle);
    }

    return (n_bytes_read == in_n_bytes);
}

bool APIDumpLoader::WorkloadReader::read_data_chunk(DataChunk* out_data_chunk_ptr)
{
    uint32_t n_bytes = 0;
    bool     result  = false;

    if (peek(sizeof(uint32_t) ) < sizeof(uint32_t) )
    {
        goto end;
    }

    memcpy(&n_bytes,
           m_buffer_u8_vec.data() + m_buffer_start,
           sizeof(uint32_t) );

    m_buffer_start += sizeof(uint32_t);

    if (n_bytes > MAX_ITEM_N_BYTES)
    {
        goto end;
    }

    out_data_chunk_ptr->resize(n_bytes);

    result = read_bytes(out_data_chunk_ptr->data(),
                        n_bytes);
end:
    return result;
}

bool APIDumpLoader::WorkloadReader::read_next_segment(Workload* out_workload_ptr)
{
    constexpr size_t N_COUNTS = 3; /* API calls, data chunks, surfaces */

    uint32_t     counts_u32vec3[N_COUNTS] = {};
    size_t       n_bytes_available        = 0;
    bool         result                   = false;
    const size_t segment_header_n_bytes   = sizeof(uint32_t) * N_COUNTS;

    /* A segment which ends abruptly is still returned, as far as it goes. */
    const auto mark_truncated_func = [&]()
    {
        m_is_truncated = true;
        m_is_finished  = true;
    };

    if (m_is_finished)
    {
        goto end;
    }

    n_bytes_available = peek(segment_header_n_bytes);

    if (n_bytes_available == 0)
    {
        /* Clean end of file. */
        m_is_finished = true;

        goto end;
    }

    if (n_bytes_available < segment_header_n_bytes)
    {
        mark_truncated_func();

        goto end;
    }

    memcpy(counts_u32vec3,
           m_buffer_u8_vec.data() + m_buffer_start,
           segment_header_n_bytes);

    m_buffer_start += segment_header_n_bytes;

    out_workload_ptr->data_chunk_ptr_vec.clear();
    out_workload_ptr->dumped_api_call_vec_ptr.reset(new DumpedAPICallVector() );
    out_workload_ptr->dumped_surface_vec_ptr.reset (new DumpedSurfaceVector() );
    out_workload_ptr->first_data_chunk_id = m_n_data_chunks_read;

    result = true;

    for (uint32_t n_api_call = 0;
                  n_api_call < counts_u32vec3[0];
                ++n_api_call)
    {
        DumpedAPICall new_api_call;

        if (read_api_call(&new_api_call) == false)
        {
            mark_truncated_func();

            goto end;
        }

        out_workload_ptr->dumped_api_call_vec_ptr->emplace_back(std::move(new_api_call) );
    }

    for (uint32_t n_data_chunk = 0;
                  n_data_chunk < counts_u32vec3[1];
                ++n_data_chunk)
    {
        DataChunkUniquePtr new_data_chunk_ptr(new DataChunk() );

        if (read_data_chunk(new_data_chunk_ptr.get() ) == false)
        {
            mark_truncated_func();

            goto end;
        }

        out_workload_ptr->data_chunk_ptr_vec.emplace_back(std::move(new_data_chunk_ptr) );

        m_n_data_chunks_read++;
    }

    for (uint32_t n_surface = 0;
                  n_surface < counts_u32vec3[2];
                ++n_surface)
    {
        DumpedSurface new_surface;

        if (read_surface(&new_surface) == false)
        {
            mark_truncated_func();

            goto end;
        }

        out_workload_ptr->dumped_surface_vec_ptr->emplace_back(std::move(new_surface) );
    }

end:
    return result;
}

bool APIDumpLoader::WorkloadReader::read_surface(DumpedSurface* out_surface_ptr)
{
    constexpr size_t N_HEADER_FIELDS = 3; /* width, height, n bytes */

    uint32_t     header_u32vec3[N_HEADER_FIELDS] = {};
    const size_t header_n_bytes                  = sizeof(uint32_t) * N_HEADER_FIELDS;
    bool         result                          = false;

    if (peek(header_n_bytes) < header_n_bytes)
    {
        goto end;
    }

    memcpy(header_u32vec3,
           m_buffer_u8_vec.data() + m_buffer_start,
           header_n_bytes);

    m_buffer_start += header_n_bytes;

    if (header_u32vec3[2] > MAX_ITEM_N_BYTES)
    {
        goto end;
    }

    out_surface_ptr->extents_u32vec2[0] = header_u32vec3[0];
    out_surface_ptr->extents_u32vec2[1] = header_u32vec3[1];

    out_surface_ptr->data_u8_vec.resize(header_u32vec3[2]);

    result = read_bytes(out_surface_ptr->data_u8_vec.data(),
                        header_u32vec3[2]);
end:
    return result;
}

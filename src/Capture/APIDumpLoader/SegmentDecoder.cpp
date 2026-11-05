/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Capture/APIDumpLoader/SegmentDecoder.h"
#include "Capture/APIDumpLoader/api_info.h"
#include "Common/workload_format.h"
#include <algorithm>
#include <string.h>

/* What is held of the decompressed bytes at a time. */
static constexpr size_t BUFFER_N_BYTES = 1024 * 1024;

/* An item bigger than MAX_ITEM_N_BYTES is a sign of corruption. */
static constexpr uint32_t MAX_ITEM_N_BYTES = 1u << 30; /* 1 GiB */

Capture::APIDumpLoader::FrameStream::FrameStream(ZSTD_DCtx*     in_decompressor_ptr,
                                                 const uint8_t* in_frame_ptr,
                                                 const size_t&  in_n_frame_bytes)
    :m_buffer_end       (0),
     m_buffer_start     (0),
     m_decompressor_ptr (in_decompressor_ptr),
     m_input            ({in_frame_ptr, in_n_frame_bytes, 0}),
     m_is_broken        (false),
     m_is_frame_done    (false)
{
    /* The padding keeps parsing code from reading outside the buffer when a frame ends early. */
    m_buffer_u8_vec.resize(BUFFER_N_BYTES + MAX_PEEK_N_BYTES);

    ::ZSTD_DCtx_reset(m_decompressor_ptr,
                      ZSTD_reset_session_only);
}

void Capture::APIDumpLoader::FrameStream::consume(const size_t& in_n_bytes)
{
    m_buffer_start += in_n_bytes;
}

size_t Capture::APIDumpLoader::FrameStream::decompress(void*         out_data_ptr,
                                                       const size_t& in_n_bytes)
{
    ZSTD_outBuffer output = {out_data_ptr, in_n_bytes, 0};

    while (output.pos <  output.size &&
           m_is_broken     == false  &&
           m_is_frame_done == false)
    {
        const size_t n_bytes_in_before  = m_input.pos;
        const size_t n_bytes_out_before = output.pos;
        const size_t n_bytes_expected   = ::ZSTD_decompressStream(m_decompressor_ptr,
                                                                 &output,
                                                                 &m_input);

        if (::ZSTD_isError(n_bytes_expected) )
        {
            m_is_broken = true;
        }
        else
        if (n_bytes_expected == 0)
        {
            /* Zero means that the frame has just ended. */
            m_is_frame_done = true;
        }
        else
        if (m_input.pos == n_bytes_in_before &&
            output.pos  == n_bytes_out_before)
        {
            /* All of the frame there is has been used, and it is not over: it was cut. */
            m_is_broken = true;
        }
    }

    return output.pos;
}

bool Capture::APIDumpLoader::FrameStream::finish()
{
    /* What is left is not wanted, but the end of the frame is where it is checked. */
    m_buffer_end   = 0;
    m_buffer_start = 0;

    while (m_is_broken     == false &&
           m_is_frame_done == false)
    {
        decompress(m_buffer_u8_vec.data(),
                   BUFFER_N_BYTES);
    }

    return (m_is_broken == false);
}

const uint8_t* Capture::APIDumpLoader::FrameStream::get_buffered_ptr() const
{
    return m_buffer_u8_vec.data() + m_buffer_start;
}

bool Capture::APIDumpLoader::FrameStream::is_broken() const
{
    return m_is_broken;
}

size_t Capture::APIDumpLoader::FrameStream::peek(const size_t& in_n_bytes)
{
    if (m_buffer_end - m_buffer_start < in_n_bytes)
    {
        /* Move what is left to the front, and top the buffer up. */
        const size_t n_bytes_left = m_buffer_end - m_buffer_start;

        ::memmove(m_buffer_u8_vec.data(),
                  m_buffer_u8_vec.data() + m_buffer_start,
                  n_bytes_left);

        m_buffer_start = 0;
        m_buffer_end   = n_bytes_left;
        m_buffer_end  += decompress(m_buffer_u8_vec.data() + m_buffer_end,
                                    BUFFER_N_BYTES - m_buffer_end);

        ::memset(m_buffer_u8_vec.data() + m_buffer_end,
                 0,
                 MAX_PEEK_N_BYTES);
    }

    return m_buffer_end - m_buffer_start;
}

bool Capture::APIDumpLoader::FrameStream::read_bytes(void*         out_data_ptr,
                                                     const size_t& in_n_bytes)
{
    const size_t n_bytes_buffered = std::min<size_t>(in_n_bytes,
                                                     m_buffer_end - m_buffer_start);
    size_t       n_bytes_read     = n_bytes_buffered;

    if (n_bytes_buffered != 0)
    {
        ::memcpy(out_data_ptr,
                 m_buffer_u8_vec.data() + m_buffer_start,
                 n_bytes_buffered);

        m_buffer_start += n_bytes_buffered;
    }

    /* The rest does not go through the buffer. */
    if (n_bytes_read < in_n_bytes)
    {
        n_bytes_read += decompress(static_cast<uint8_t*>(out_data_ptr) + n_bytes_read,
                                   in_n_bytes - n_bytes_read);
    }

    return (n_bytes_read == in_n_bytes);
}

bool Capture::APIDumpLoader::FrameStream::skip_bytes(const size_t& in_n_bytes)
{
    const size_t n_bytes_buffered = std::min<size_t>(in_n_bytes,
                                                     m_buffer_end - m_buffer_start);
    size_t       n_bytes_left     = in_n_bytes - n_bytes_buffered;

    m_buffer_start += n_bytes_buffered;

    if (n_bytes_left != 0)
    {
        /* The buffer is empty now, and is where the bytes go to be forgotten. */
        m_buffer_end   = 0;
        m_buffer_start = 0;

        while (n_bytes_left != 0)
        {
            const size_t n_bytes_got = decompress(m_buffer_u8_vec.data(),
                                                  std::min<size_t>(n_bytes_left,
                                                                   BUFFER_N_BYTES) );

            if (n_bytes_got == 0)
            {
                break;
            }

            n_bytes_left -= n_bytes_got;
        }

        /* The padding must stay zeros for what is read after it. */
        ::memset(m_buffer_u8_vec.data(),
                 0,
                 MAX_PEEK_N_BYTES);
    }

    return (n_bytes_left == 0);
}

std::vector<bool> Capture::APIDumpLoader::SegmentDecoder::find_unwanted_chunks(const DumpedAPICallVector& in_call_vec,
                                                                               const Options&             in_options,
                                                                               const size_t&              in_n_chunks)
{
    enum class ChunkUse : uint8_t
    {
        NOT_REFERRED,
        REFERRED_BY_UNWANTING_CALLS_ONLY,
        WANTED
    };

    uint64_t              frame_index = in_options.first_frame_index;
    std::vector<ChunkUse> use_vec(in_n_chunks,
                                  ChunkUse::NOT_REFERRED);
    std::vector<bool>     result(in_n_chunks,
                                 false);

    for (const auto& call : in_call_vec)
    {
        const bool is_wanted = in_options.chunk_wanted_func(call,
                                                            frame_index);

        for (const auto* arg_vec_ptr : {&call.arg_in_vec, &call.arg_out_vec})
        {
            for (const auto& arg : *arg_vec_ptr)
            {
                if (arg.type == APIInterceptor::ARGTYPE_DATA_CHUNK_ID)
                {
                    const uint32_t n_chunk = arg.get_data_chunk_id() - in_options.first_data_chunk_id;

                    if (arg.get_data_chunk_id() >= in_options.first_data_chunk_id &&
                        n_chunk                 <  in_n_chunks)
                    {
                        if (is_wanted)
                        {
                            use_vec.at(n_chunk) = ChunkUse::WANTED;
                        }
                        else
                        if (use_vec.at(n_chunk) == ChunkUse::NOT_REFERRED)
                        {
                            use_vec.at(n_chunk) = ChunkUse::REFERRED_BY_UNWANTING_CALLS_ONLY;
                        }
                    }
                }
            }
        }

        if (is_frame_boundary(call) )
        {
            frame_index++;
        }
    }

    for (size_t n_chunk = 0;
                n_chunk < in_n_chunks;
              ++n_chunk)
    {
        result.at(n_chunk) = (use_vec.at(n_chunk) == ChunkUse::REFERRED_BY_UNWANTING_CALLS_ONLY);
    }

    return result;
}

bool Capture::APIDumpLoader::SegmentDecoder::parse_api_call(FrameStream*   inout_stream_ptr,
                                                            DumpedAPICall* out_api_call_ptr)
{
    constexpr size_t   HEADER_N_BYTES           = APIInterceptor::WorkloadFormat::CALL_HEADER_N_BYTES;
    constexpr size_t   MAX_ARGUMENT_N_BYTES     = 16;                                                         /* type and the widest payload */
    constexpr uint32_t MAX_N_ARGUMENTS_PER_CALL = 64;

    const uint8_t*                      header_u8_ptr   = nullptr;
    uint32_t                            n_in_arguments  = 0;
    uint32_t                            n_out_arguments = 0;
    bool                                result          = false;
    APIInterceptor::APIFunctionArgument returned_value;

    /* Reads one argument. */
    const auto parse_argument_func = [&](APIInterceptor::APIFunctionArgument* out_argument_ptr)
    {
        const size_t n_bytes_available = inout_stream_ptr->peek(MAX_ARGUMENT_N_BYTES);
        uint32_t     n_bytes_used      = 0;
        bool         is_ok             = false;

        if (n_bytes_available != 0)
        {
            n_bytes_used = out_argument_ptr->deserialize_from_u8_ptr(inout_stream_ptr->get_buffered_ptr() );

            if (n_bytes_used <= n_bytes_available)
            {
                inout_stream_ptr->consume(n_bytes_used);

                is_ok = true;
            }
        }

        return is_ok;
    };

    if (inout_stream_ptr->peek(HEADER_N_BYTES) < HEADER_N_BYTES)
    {
        goto end;
    }

    header_u8_ptr = inout_stream_ptr->get_buffered_ptr();

    ::memcpy(&out_api_call_ptr->func,
             header_u8_ptr,
             sizeof(APIInterceptor::APIFunction) );
    ::memcpy(&n_in_arguments,
             header_u8_ptr + sizeof(APIInterceptor::APIFunction),
             sizeof(uint32_t) );
    ::memcpy(&n_out_arguments,
             header_u8_ptr + sizeof(APIInterceptor::APIFunction) + sizeof(uint32_t),
             sizeof(uint32_t) );
    ::memcpy(&out_api_call_ptr->thread_id,
             header_u8_ptr + sizeof(APIInterceptor::APIFunction) + 2 * sizeof(uint32_t),
             sizeof(uint32_t) );
    ::memcpy(&out_api_call_ptr->timestamp_qpc,
             header_u8_ptr + sizeof(APIInterceptor::APIFunction) + 3 * sizeof(uint32_t),
             sizeof(uint64_t) );

    inout_stream_ptr->consume(HEADER_N_BYTES);

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
        if (parse_argument_func(&current_argument) == false)
        {
            goto end;
        }
    }

    for (auto& current_argument : out_api_call_ptr->arg_out_vec)
    {
        if (parse_argument_func(&current_argument) == false)
        {
            goto end;
        }
    }

    if (parse_argument_func(&returned_value) == false)
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

bool Capture::APIDumpLoader::SegmentDecoder::parse_data_chunk(FrameStream*   inout_stream_ptr,
                                                              const Options& in_options,
                                                              const bool&    in_is_unwanted,
                                                              DataChunk*     out_data_chunk_ptr)
{
    uint32_t n_bytes = 0;
    bool     result  = false;

    if (inout_stream_ptr->peek(sizeof(uint32_t) ) < sizeof(uint32_t) )
    {
        goto end;
    }

    ::memcpy(&n_bytes,
             inout_stream_ptr->get_buffered_ptr(),
             sizeof(uint32_t) );

    inout_stream_ptr->consume(sizeof(uint32_t) );

    if (n_bytes > MAX_ITEM_N_BYTES)
    {
        goto end;
    }

    if (in_is_unwanted                                           ||
        (in_options.skip_data_chunks_above_n_bytes != 0           &&
         n_bytes                                   >  in_options.skip_data_chunks_above_n_bytes) )
    {
        result = inout_stream_ptr->skip_bytes(n_bytes);

        goto end;
    }

    out_data_chunk_ptr->resize(n_bytes);

    result = inout_stream_ptr->read_bytes(out_data_chunk_ptr->data(),
                                          n_bytes);
end:
    return result;
}

bool Capture::APIDumpLoader::SegmentDecoder::parse_segment(FrameStream*   inout_stream_ptr,
                                                           const Options& in_options,
                                                           Workload*      out_workload_ptr,
                                                           bool*          out_is_truncated_ptr)
{
    constexpr size_t N_COUNTS = 3; /* API calls, data chunks, surfaces */

    uint32_t          counts_u32vec3[N_COUNTS] = {};
    std::vector<bool> is_unwanted_vec;
    bool              result                   = false;
    const size_t segment_header_n_bytes   = sizeof(uint32_t) * N_COUNTS;

    *out_is_truncated_ptr = false;

    if (inout_stream_ptr->peek(segment_header_n_bytes) < segment_header_n_bytes)
    {
        goto end;
    }

    ::memcpy(counts_u32vec3,
             inout_stream_ptr->get_buffered_ptr(),
             segment_header_n_bytes);

    inout_stream_ptr->consume(segment_header_n_bytes);

    out_workload_ptr->data_chunk_ptr_vec.clear     ();
    out_workload_ptr->dumped_api_call_vec_ptr.reset(new DumpedAPICallVector() );
    out_workload_ptr->dumped_surface_vec_ptr.reset (new DumpedSurfaceVector() );

    out_workload_ptr->first_data_chunk_id = 0;

    result = true;

    for (uint32_t n_api_call = 0;
                  n_api_call < counts_u32vec3[0];
                ++n_api_call)
    {
        DumpedAPICall new_api_call;

        if (parse_api_call(inout_stream_ptr,
                          &new_api_call) == false)
        {
            *out_is_truncated_ptr = true;

            goto end;
        }

        out_workload_ptr->dumped_api_call_vec_ptr->emplace_back(std::move(new_api_call) );
    }

    if (in_options.chunk_wanted_func)
    {
        is_unwanted_vec = find_unwanted_chunks(*out_workload_ptr->dumped_api_call_vec_ptr,
                                               in_options,
                                               counts_u32vec3[1]);
    }

    for (uint32_t n_data_chunk = 0;
                  n_data_chunk < counts_u32vec3[1];
                ++n_data_chunk)
    {
        DataChunkUniquePtr new_data_chunk_ptr(new DataChunk() );

        if (parse_data_chunk(inout_stream_ptr,
                             in_options,
                             (is_unwanted_vec.empty() == false) && is_unwanted_vec.at(n_data_chunk),
                             new_data_chunk_ptr.get() ) == false)
        {
            *out_is_truncated_ptr = true;

            goto end;
        }

        out_workload_ptr->data_chunk_ptr_vec.emplace_back(std::move(new_data_chunk_ptr) );
    }

    for (uint32_t n_surface = 0;
                  n_surface < counts_u32vec3[2];
                ++n_surface)
    {
        DumpedSurface new_surface;

        if (parse_surface(inout_stream_ptr,
                         &new_surface) == false)
        {
            *out_is_truncated_ptr = true;

            goto end;
        }

        out_workload_ptr->dumped_surface_vec_ptr->emplace_back(std::move(new_surface) );
    }

end:
    return result;
}

bool Capture::APIDumpLoader::SegmentDecoder::parse_surface(FrameStream*   inout_stream_ptr,
                                                           DumpedSurface* out_surface_ptr)
{
    constexpr size_t N_HEADER_FIELDS = 3; /* width, height, n bytes */

    uint32_t     header_u32vec3[N_HEADER_FIELDS] = {};
    const size_t header_n_bytes                  = sizeof(uint32_t) * N_HEADER_FIELDS;
    bool         result                          = false;

    if (inout_stream_ptr->peek(header_n_bytes) < header_n_bytes)
    {
        goto end;
    }

    ::memcpy(header_u32vec3,
             inout_stream_ptr->get_buffered_ptr(),
             header_n_bytes);

    inout_stream_ptr->consume(header_n_bytes);

    if (header_u32vec3[2] > MAX_ITEM_N_BYTES)
    {
        goto end;
    }

    out_surface_ptr->extents_u32vec2[0] = header_u32vec3[0];
    out_surface_ptr->extents_u32vec2[1] = header_u32vec3[1];

    out_surface_ptr->data_u8_vec.resize(header_u32vec3[2]);

    result = inout_stream_ptr->read_bytes(out_surface_ptr->data_u8_vec.data(),
                                          header_u32vec3[2]);
end:
    return result;
}

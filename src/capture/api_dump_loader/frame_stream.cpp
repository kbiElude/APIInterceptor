/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "capture/api_dump_loader/frame_stream.h"
#include <algorithm>
#include <string.h>

/* What is held of the decompressed bytes at a time. */
static constexpr size_t BUFFER_N_BYTES = 1024 * 1024;

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

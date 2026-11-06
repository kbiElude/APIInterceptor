/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "zstd_file_writer.h"

Capture::APIDumperDLL::ZstdFileWriter::ZstdFileWriter()
    :m_compressor_ptr(nullptr),
     m_file_handle   (nullptr)
{
    /* Stub */
}

Capture::APIDumperDLL::ZstdFileWriter::~ZstdFileWriter()
{
    if (m_compressor_ptr != nullptr)
    {
        ::ZSTD_freeCCtx(m_compressor_ptr);
    }
}

bool Capture::APIDumperDLL::ZstdFileWriter::compress(const void*              in_data_ptr,
                                                     const size_t&            in_n_bytes,
                                                     const ZSTD_EndDirective& in_directive)
{
    ZSTD_inBuffer input             = {in_data_ptr, in_n_bytes, 0};
    size_t        n_bytes_remaining = 0;
    bool          result            = false;

    do
    {
        ZSTD_outBuffer output = {m_output_u8_vec.data(), m_output_u8_vec.size(), 0};

        n_bytes_remaining = ::ZSTD_compressStream2(m_compressor_ptr,
                                                  &output,
                                                  &input,
                                                   in_directive);

        if (::ZSTD_isError(n_bytes_remaining) )
        {
            goto end;
        }

        if (output.pos != 0)
        {
            if (::fwrite(m_output_u8_vec.data(),
                         output.pos,
                         1,
                         m_file_handle) != 1)
            {
                goto end;
            }
        }
    }
    while (input.pos          <  input.size ||
           (in_directive      == ZSTD_e_end &&
            n_bytes_remaining != 0) );

    result = true;
end:
    return result;
}

Capture::APIDumperDLL::ZstdFileWriterUniquePtr Capture::APIDumperDLL::ZstdFileWriter::create(FILE*      in_file_handle,
                                                                                             const int& in_compression_level)
{
    ZstdFileWriterUniquePtr result_ptr(new ZstdFileWriter() );

    result_ptr->m_compressor_ptr = ::ZSTD_createCCtx();
    result_ptr->m_file_handle    = in_file_handle;

    if (result_ptr->m_compressor_ptr == nullptr)
    {
        result_ptr.reset();

        goto end;
    }

    /* A damaged file is then noticed by the reader, instead of being replayed wrongly. */
    ::ZSTD_CCtx_setParameter(result_ptr->m_compressor_ptr,
                             ZSTD_c_checksumFlag,
                             1);
    ::ZSTD_CCtx_setParameter(result_ptr->m_compressor_ptr,
                             ZSTD_c_compressionLevel,
                             in_compression_level);

    result_ptr->m_output_u8_vec.resize(::ZSTD_CStreamOutSize() );

end:
    return result_ptr;
}

bool Capture::APIDumperDLL::ZstdFileWriter::finish()
{
    return compress(nullptr,
                    0,
                    ZSTD_e_end);
}

bool Capture::APIDumperDLL::ZstdFileWriter::write(const void*   in_data_ptr,
                                                  const size_t& in_n_bytes)
{
    return compress(in_data_ptr,
                    in_n_bytes,
                    ZSTD_e_continue);
}

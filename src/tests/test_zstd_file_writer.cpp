/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Tests for ZstdFileWriter: what is written comes back as it was, as one frame, whether the compressor works with threads of its own or not.
 */
#include <gtest/gtest.h>
#include "capture/api_dumper_dll/zstd_file_writer.h"
#include <algorithm>
#include <stdint.h>
#include <string.h>
#include <vector>

namespace
{
    /* Bytes that repeat in a pattern which differs from piece to piece, so that they compress, but not to nothing. */
    std::vector<uint8_t> make_data(const size_t& in_n_bytes)
    {
        std::vector<uint8_t> result_u8vec(in_n_bytes);

        for (size_t n_byte = 0;
                    n_byte < in_n_bytes;
                  ++n_byte)
        {
            result_u8vec.at(n_byte) = static_cast<uint8_t>( (n_byte * 31 + (n_byte >> 12) ) & 0xff);
        }

        return result_u8vec;
    }

    /* Writes the data in pieces of the sizes that the dumper does (a few bytes of a call, then a big chunk), and returns the file. */
    std::vector<uint8_t> write_and_read_back(const std::vector<uint8_t>& in_data_u8vec,
                                             const int&                  in_n_workers)
    {
        constexpr int    COMPRESSION_LEVEL = 3;
        constexpr size_t SMALL_PIECE       = 37;
        constexpr size_t BIG_PIECE         = 900000;

        FILE* const file_handle = ::tmpfile();

        std::vector<uint8_t> result_u8vec;

        if (file_handle == nullptr)
        {
            return result_u8vec;
        }

        auto writer_ptr = Capture::APIDumperDLL::ZstdFileWriter::create(file_handle,
                                                                        COMPRESSION_LEVEL,
                                                                        in_n_workers);

        if (writer_ptr != nullptr)
        {
            size_t n_written = 0;
            bool   is_small  = true;

            while (n_written < in_data_u8vec.size() )
            {
                const size_t n_piece = std::min( (is_small) ? SMALL_PIECE
                                                            : BIG_PIECE,
                                                in_data_u8vec.size() - n_written);

                writer_ptr->write(in_data_u8vec.data() + n_written,
                                  n_piece);

                n_written += n_piece;
                is_small   = !is_small;
            }

            writer_ptr->finish();
        }

        ::fflush(file_handle);
        ::fseek (file_handle, 0, SEEK_END);

        result_u8vec.resize(static_cast<size_t>(::ftell(file_handle) ) );

        ::fseek(file_handle, 0, SEEK_SET);
        ::fread(result_u8vec.data(), 1, result_u8vec.size(), file_handle);
        ::fclose(file_handle);

        return result_u8vec;
    }

    void expect_one_frame_of(const std::vector<uint8_t>& in_file_u8vec,
                             const std::vector<uint8_t>& in_data_u8vec)
    {
        ASSERT_FALSE(in_file_u8vec.empty() );

        /* The whole file is one frame. */
        EXPECT_EQ(::ZSTD_findFrameCompressedSize(in_file_u8vec.data(),
                                                 in_file_u8vec.size() ),
                  in_file_u8vec.size() );

        std::vector<uint8_t> decoded_u8vec(in_data_u8vec.size() );
        const size_t         n_decoded = ::ZSTD_decompress(decoded_u8vec.data(),
                                                           decoded_u8vec.size(),
                                                           in_file_u8vec.data(),
                                                           in_file_u8vec.size() );

        ASSERT_FALSE(::ZSTD_isError(n_decoded) ) << ::ZSTD_getErrorName(n_decoded);
        EXPECT_EQ   (n_decoded,
                     in_data_u8vec.size() );
        EXPECT_EQ   (decoded_u8vec,
                     in_data_u8vec);
    }
}

TEST(ZstdFileWriter, WhatIsWrittenComesBackAsOneFrameWithoutThreads)
{
    const auto data_u8vec = make_data(5000000);

    expect_one_frame_of(write_and_read_back(data_u8vec,
                                            0), /* in_n_workers */
                        data_u8vec);
}

TEST(ZstdFileWriter, WhatIsWrittenComesBackAsOneFrameWithThreads)
{
    const auto data_u8vec = make_data(5000000);

    expect_one_frame_of(write_and_read_back(data_u8vec,
                                            4), /* in_n_workers */
                        data_u8vec);
}

TEST(ZstdFileWriter, NothingWrittenIsStillAFrameThatDecodesToNothing)
{
    const std::vector<uint8_t> data_u8vec;

    expect_one_frame_of(write_and_read_back(data_u8vec,
                                            4), /* in_n_workers */
                        data_u8vec);
}

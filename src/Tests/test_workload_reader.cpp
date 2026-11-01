/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of reading workload files segment by segment.
 */
#include <gtest/gtest.h>
#include "Capture/APIDumpLoader/APIDumpLoader.h"
#include "Capture/APIDumpLoader/WorkloadReader.h"
#include "Common/workload_format.h"
#include "workload_file_builder.h"
#include <stdio.h>
#include <string.h>
#include <string>

TEST(WorkloadReader, ReadsSegmentsOneAtATime)
{
    std::vector<uint8_t>    file_u8_vec;
    bool                    is_second_read_ok = false;
    Capture::APIDumpLoader::Workload segment;

    Tests::WorkloadFileBuilder::build_two_segments(&file_u8_vec);
    Tests::WorkloadFileBuilder::write_file(file_u8_vec);

    auto reader_ptr = Capture::APIDumpLoader::WorkloadReader::create(Tests::WorkloadFileBuilder::get_filename_ptr());

    ASSERT_NE(reader_ptr,
              nullptr);

    ASSERT_TRUE(reader_ptr->read_next_segment(&segment) );
    EXPECT_EQ(segment.dumped_api_call_vec_ptr->size(),
              2u);
    EXPECT_EQ(segment.data_chunk_ptr_vec.size(),
              2u);
    EXPECT_EQ(segment.dumped_surface_vec_ptr->size(),
              1u);
    EXPECT_EQ(segment.first_data_chunk_id,
              0u);
    EXPECT_EQ(segment.dumped_api_call_vec_ptr->at(1).arg_in_vec.at(0).get_u32(),
              11u);
    EXPECT_EQ(segment.dumped_surface_vec_ptr->at(0).data_u8_vec.size(),
              8u);

    is_second_read_ok = reader_ptr->read_next_segment(&segment);

    ASSERT_TRUE(is_second_read_ok);
    EXPECT_EQ(segment.dumped_api_call_vec_ptr->size(),
              1u);
    EXPECT_EQ(segment.first_data_chunk_id,
              2u);

    /* Chunk IDs count across segments; only the current segment's chunks are held. */
    EXPECT_EQ(Capture::APIDumpLoader::get_data_chunk_ptr(segment,
                                                         0),
                       nullptr);
    ASSERT_NE(Capture::APIDumpLoader::get_data_chunk_ptr(segment,
                                                         2),
                       nullptr);
    EXPECT_EQ(Capture::APIDumpLoader::get_data_chunk_ptr(segment,
                                                         2)->size(),
                       4u);
    EXPECT_EQ(Capture::APIDumpLoader::get_data_chunk_ptr(segment,
                                                         3),
                       nullptr);

    EXPECT_FALSE(reader_ptr->read_next_segment(&segment) );
    EXPECT_FALSE(reader_ptr->is_truncated() );

    reader_ptr.reset();
    ::remove(Tests::WorkloadFileBuilder::get_filename_ptr());
}

TEST(WorkloadReader, ReturnsWhatIsCompleteFromATruncatedFile)
{
    std::vector<uint8_t>    file_u8_vec;
    Capture::APIDumpLoader::Workload segment;

    /* The last segment ends in the middle of the last chunk. */
    Tests::WorkloadFileBuilder::build_two_segments(&file_u8_vec,
                                                   2); /* in_n_bytes_to_drop_from_second_segment */
    Tests::WorkloadFileBuilder::write_file        (file_u8_vec);

    auto reader_ptr = Capture::APIDumpLoader::WorkloadReader::create(Tests::WorkloadFileBuilder::get_filename_ptr());

    ASSERT_NE(reader_ptr,
              nullptr);
    ASSERT_TRUE(reader_ptr->read_next_segment(&segment) );
    EXPECT_FALSE(reader_ptr->is_truncated() );

    ASSERT_TRUE(reader_ptr->read_next_segment(&segment) );
    EXPECT_TRUE(reader_ptr->is_truncated() );
    EXPECT_EQ(segment.dumped_api_call_vec_ptr->size(),
              1u);
    EXPECT_EQ(segment.data_chunk_ptr_vec.size(),
              0u);

    EXPECT_FALSE(reader_ptr->read_next_segment(&segment) );

    reader_ptr.reset();
    ::remove(Tests::WorkloadFileBuilder::get_filename_ptr());
}

TEST(WorkloadReader, ReadsAChunkLargerThanTheBuffers)
{
    std::vector<uint8_t>    file_u8_vec;
    Capture::APIDumpLoader::Workload segment;

    Tests::WorkloadFileBuilder::build_large_chunk(&file_u8_vec);
    Tests::WorkloadFileBuilder::write_file       (file_u8_vec);

    auto reader_ptr = Capture::APIDumpLoader::WorkloadReader::create(Tests::WorkloadFileBuilder::get_filename_ptr());

    ASSERT_NE(reader_ptr,
              nullptr);
    ASSERT_TRUE(reader_ptr->read_next_segment(&segment) );
    ASSERT_EQ(segment.data_chunk_ptr_vec.size(),
              1u);
    ASSERT_EQ(segment.data_chunk_ptr_vec.at(0)->size(),
              Tests::WorkloadFileBuilder::LARGE_CHUNK_N_BYTES);

    for (size_t n_byte = 0;
                n_byte < Tests::WorkloadFileBuilder::LARGE_CHUNK_N_BYTES;
              ++n_byte)
    {
        ASSERT_EQ(segment.data_chunk_ptr_vec.at(0)->at(n_byte),
                  Tests::WorkloadFileBuilder::get_large_chunk_byte(n_byte) ) << "byte " << n_byte;
    }

    EXPECT_FALSE(reader_ptr->read_next_segment(&segment) );
    EXPECT_FALSE(reader_ptr->is_truncated() );

    reader_ptr.reset();
    ::remove(Tests::WorkloadFileBuilder::get_filename_ptr());
}

TEST(WorkloadReader, ReturnsWhatIsCompleteFromAFrameWhichEndsAbruptly)
{
    std::vector<uint8_t>    file_u8_vec;
    Capture::APIDumpLoader::Workload segment;

    Tests::WorkloadFileBuilder::build_large_chunk(&file_u8_vec);

    /* The file ends in the middle of the frame, long after the call and before the end of the chunk. */
    file_u8_vec.resize(file_u8_vec.size() / 2);
    Tests::WorkloadFileBuilder::write_file(file_u8_vec);

    auto reader_ptr = Capture::APIDumpLoader::WorkloadReader::create(Tests::WorkloadFileBuilder::get_filename_ptr());

    ASSERT_NE(reader_ptr,
              nullptr);
    ASSERT_TRUE(reader_ptr->read_next_segment(&segment) );
    EXPECT_TRUE(reader_ptr->is_truncated() );
    EXPECT_EQ(segment.dumped_api_call_vec_ptr->size(),
              1u);
    EXPECT_EQ(segment.data_chunk_ptr_vec.size(),
              0u);

    EXPECT_FALSE(reader_ptr->read_next_segment(&segment) );

    reader_ptr.reset();
    ::remove(Tests::WorkloadFileBuilder::get_filename_ptr());
}

TEST(WorkloadReader, ReportsAMissingFrameAsTruncation)
{
    constexpr size_t N_BYTES_TO_CUT = 12;

    std::vector<uint8_t>    file_u8_vec;
    Capture::APIDumpLoader::Workload segment;

    Tests::WorkloadFileBuilder::build_two_segments(&file_u8_vec);

    /* Little is left of the second frame. */
    file_u8_vec.resize(file_u8_vec.size() - N_BYTES_TO_CUT);
    Tests::WorkloadFileBuilder::write_file(file_u8_vec);

    auto reader_ptr = Capture::APIDumpLoader::WorkloadReader::create(Tests::WorkloadFileBuilder::get_filename_ptr());

    ASSERT_NE(reader_ptr,
              nullptr);
    ASSERT_TRUE(reader_ptr->read_next_segment(&segment) );
    EXPECT_FALSE(reader_ptr->is_truncated() );

    while (reader_ptr->read_next_segment(&segment) )
    {
        /* Whatever is returned from the second segment, the loop must end. */
    }

    EXPECT_TRUE(reader_ptr->is_truncated() );

    reader_ptr.reset();
    ::remove(Tests::WorkloadFileBuilder::get_filename_ptr());
}

TEST(WorkloadReader, RejectsDamagedData)
{
    constexpr int GARBAGE_BYTE = 0xA5;

    std::vector<uint8_t>    file_u8_vec;
    Capture::APIDumpLoader::Workload segment;

    Tests::WorkloadFileBuilder::build_large_chunk(&file_u8_vec);

    /* Garbage in the place of the compressed data. */
    ::memset(file_u8_vec.data() + sizeof(APIInterceptor::WorkloadFormat::WorkloadFileHeader),
             GARBAGE_BYTE,
             file_u8_vec.size() - sizeof(APIInterceptor::WorkloadFormat::WorkloadFileHeader) );
    Tests::WorkloadFileBuilder::write_file(file_u8_vec);

    auto reader_ptr = Capture::APIDumpLoader::WorkloadReader::create(Tests::WorkloadFileBuilder::get_filename_ptr());

    ASSERT_NE(reader_ptr,
              nullptr);
    EXPECT_FALSE(reader_ptr->read_next_segment(&segment) );
    EXPECT_TRUE (reader_ptr->is_truncated() );

    reader_ptr.reset();
    ::remove(Tests::WorkloadFileBuilder::get_filename_ptr());
}

TEST(WorkloadReader, WholeFileLoadingJoinsTheSegments)
{
    std::vector<uint8_t>    file_u8_vec;

    Tests::WorkloadFileBuilder::build_two_segments(&file_u8_vec);
    Tests::WorkloadFileBuilder::write_file(file_u8_vec);

    auto workload_ptr = Capture::APIDumpLoader::create_workload_from_file(Tests::WorkloadFileBuilder::get_filename_ptr());

    ASSERT_NE(workload_ptr,
              nullptr);
    EXPECT_EQ(workload_ptr->dumped_api_call_vec_ptr->size(),
              3u);
    EXPECT_EQ(workload_ptr->data_chunk_ptr_vec.size(),
              3u);
    EXPECT_EQ(workload_ptr->dumped_surface_vec_ptr->size(),
              1u);
    EXPECT_EQ(workload_ptr->first_data_chunk_id,
              0u);
    EXPECT_EQ(Capture::APIDumpLoader::get_data_chunk_ptr(*workload_ptr,
                                                         2)->size(),
                       4u);

    ::remove(Tests::WorkloadFileBuilder::get_filename_ptr());
}

TEST(WorkloadReader, MissingFileCannotBeOpened)
{
    EXPECT_EQ(Capture::APIDumpLoader::WorkloadReader::create("this_file_does_not_exist.workload"),
                       nullptr);
}

TEST(WorkloadReader, ExposesFileHeaderAndCallHeaderFields)
{
    std::vector<uint8_t>    file_u8_vec;
    Capture::APIDumpLoader::Workload segment;

    Tests::WorkloadFileBuilder::build_two_segments(&file_u8_vec);
    Tests::WorkloadFileBuilder::write_file(file_u8_vec);

    auto reader_ptr = Capture::APIDumpLoader::WorkloadReader::create(Tests::WorkloadFileBuilder::get_filename_ptr());

    ASSERT_NE(reader_ptr,
              nullptr);
    ASSERT_TRUE(reader_ptr->read_next_segment(&segment) );

    EXPECT_EQ(segment.pointer_n_bytes,
              static_cast<uint32_t>(Tests::WorkloadFileBuilder::POINTER_N_BYTES) );
    EXPECT_EQ(segment.qpc_frequency,
              static_cast<uint64_t>(Tests::WorkloadFileBuilder::QPC_FREQUENCY) );
    EXPECT_EQ(segment.dumped_api_call_vec_ptr->at(1).thread_id,
              static_cast<uint32_t>(Tests::WorkloadFileBuilder::THREAD_ID) );
    EXPECT_EQ(segment.dumped_api_call_vec_ptr->at(1).timestamp_qpc,
              static_cast<uint64_t>(Tests::WorkloadFileBuilder::TIMESTAMP_BASE) + 11);

    reader_ptr.reset();
    ::remove(Tests::WorkloadFileBuilder::get_filename_ptr());
}

TEST(WorkloadReader, RejectsAFileWithoutTheHeader)
{
    std::string          error;
    std::vector<uint8_t> file_u8_vec;

    Tests::WorkloadFileBuilder::build_file_without_header(&file_u8_vec);
    Tests::WorkloadFileBuilder::write_file               (file_u8_vec);

    EXPECT_EQ(Capture::APIDumpLoader::WorkloadReader::create(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                                            &error),
                       nullptr);
    EXPECT_FALSE(error.empty() );

    EXPECT_EQ(Capture::APIDumpLoader::create_workload_from_file(Tests::WorkloadFileBuilder::get_filename_ptr() ),
                       nullptr);

    ::remove(Tests::WorkloadFileBuilder::get_filename_ptr());
}

TEST(WorkloadReader, FindsTheCallsOfAnAPIGroup)
{
    std::vector<uint8_t> file_u8_vec;

    Tests::WorkloadFileBuilder::build_frames(&file_u8_vec,
                                             1,  /* in_n_frames          */
                                             1); /* in_n_calls_per_frame */

    Tests::WorkloadFileBuilder::write_file(file_u8_vec);

    auto d3d8_reader_ptr  = Capture::APIDumpLoader::WorkloadReader::create(Tests::WorkloadFileBuilder::get_filename_ptr());
    auto gdi32_reader_ptr = Capture::APIDumpLoader::WorkloadReader::create(Tests::WorkloadFileBuilder::get_filename_ptr());

    ASSERT_NE(d3d8_reader_ptr,
              nullptr);
    ASSERT_NE(gdi32_reader_ptr,
              nullptr);

    EXPECT_EQ(d3d8_reader_ptr->get_pointer_n_bytes(),
              Tests::WorkloadFileBuilder::POINTER_N_BYTES);
    EXPECT_FALSE(d3d8_reader_ptr->contains_api_group(Capture::APIDumpLoader::APIGroup::D3D8) );
    EXPECT_TRUE (gdi32_reader_ptr->contains_api_group(Capture::APIDumpLoader::APIGroup::GDI32) );
}

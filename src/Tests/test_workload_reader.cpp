/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of reading workload files segment by segment.
 */
#include <gtest/gtest.h>
#include "APIDumpLoader/APIDumpLoader.h"
#include "APIDumpLoader/WorkloadReader.h"
#include "workload_file_builder.h"
#include <stdio.h>
#include <string.h>

TEST(WorkloadReader, ReadsSegmentsOneAtATime)
{
    std::vector<uint8_t>    file_u8_vec;
    bool                    is_second_read_ok = false;
    APIDumpLoader::Workload segment;

    Tests::WorkloadFileBuilder::build_two_segments(&file_u8_vec);
    Tests::WorkloadFileBuilder::write_file(file_u8_vec);

    auto reader_ptr = APIDumpLoader::WorkloadReader::create(Tests::WorkloadFileBuilder::get_filename_ptr());

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
    EXPECT_EQ(APIDumpLoader::get_data_chunk_ptr(segment,
                                                0),
              nullptr);
    ASSERT_NE(APIDumpLoader::get_data_chunk_ptr(segment,
                                                2),
              nullptr);
    EXPECT_EQ(APIDumpLoader::get_data_chunk_ptr(segment,
                                                2)->size(),
              4u);
    EXPECT_EQ(APIDumpLoader::get_data_chunk_ptr(segment,
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
    size_t                  second_chunk_offset = 0;
    APIDumpLoader::Workload segment;

    second_chunk_offset = Tests::WorkloadFileBuilder::build_two_segments(&file_u8_vec);

    /* The file ends in the middle of the last chunk. */
    file_u8_vec.resize(second_chunk_offset + 6);
    Tests::WorkloadFileBuilder::write_file(file_u8_vec);

    auto reader_ptr = APIDumpLoader::WorkloadReader::create(Tests::WorkloadFileBuilder::get_filename_ptr());

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

TEST(WorkloadReader, WholeFileLoadingJoinsTheSegments)
{
    std::vector<uint8_t>    file_u8_vec;

    Tests::WorkloadFileBuilder::build_two_segments(&file_u8_vec);
    Tests::WorkloadFileBuilder::write_file(file_u8_vec);

    auto workload_ptr = APIDumpLoader::create_workload_from_file(Tests::WorkloadFileBuilder::get_filename_ptr());

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
    EXPECT_EQ(APIDumpLoader::get_data_chunk_ptr(*workload_ptr,
                                                2)->size(),
              4u);

    ::remove(Tests::WorkloadFileBuilder::get_filename_ptr());
}

TEST(WorkloadReader, MissingFileCannotBeOpened)
{
    EXPECT_EQ(APIDumpLoader::WorkloadReader::create("this_file_does_not_exist.workload"),
              nullptr);
}

/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of reading workload files with threads: the segments must come out as they do without them.
 */
#include <gtest/gtest.h>
#include "capture/api_dump_loader/api_dump_loader.h"
#include "capture/api_dump_loader/workload_reader.h"
#include "common/workload_format.h"
#include "workload_file_builder.h"
#include <stdio.h>
#include <string.h>
#include <vector>

/* What a reader made of a segment: enough to tell two readings apart. */
struct SegmentSummary
{
    uint64_t chunk_byte_sum      = 0;
    uint64_t first_call_argument = 0;
    uint32_t first_data_chunk_id = 0;
    uint64_t n_calls             = 0;
    uint64_t n_chunk_bytes       = 0;
    uint64_t n_chunks            = 0;
    uint64_t n_surfaces          = 0;
};

struct ReadingSummary
{
    bool                        is_truncated = false;
    std::vector<SegmentSummary> segment_vec;
};

static bool operator==(const SegmentSummary& in_a,
                       const SegmentSummary& in_b)
{
    return (in_a.chunk_byte_sum      == in_b.chunk_byte_sum      &&
            in_a.first_call_argument == in_b.first_call_argument &&
            in_a.first_data_chunk_id == in_b.first_data_chunk_id &&
            in_a.n_calls             == in_b.n_calls             &&
            in_a.n_chunk_bytes       == in_b.n_chunk_bytes       &&
            in_a.n_chunks            == in_b.n_chunks            &&
            in_a.n_surfaces          == in_b.n_surfaces);
}

/* Writes the file, reads it as the options say, and deletes it. */
static ReadingSummary read_whole_file(const std::vector<uint8_t>&                            in_file_u8_vec,
                                      const Capture::APIDumpLoader::WorkloadReader::Options& in_options)
{
    ReadingSummary                   result;
    Capture::APIDumpLoader::Workload segment;

    Tests::WorkloadFileBuilder::write_file(in_file_u8_vec);

    auto reader_ptr = Capture::APIDumpLoader::WorkloadReader::create(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                                                     in_options);

    EXPECT_NE(reader_ptr,
              nullptr);

    while (reader_ptr != nullptr                    &&
           reader_ptr->read_next_segment(&segment) )
    {
        SegmentSummary summary;

        summary.first_data_chunk_id = segment.first_data_chunk_id;
        summary.n_calls             = segment.dumped_api_call_vec_ptr->size();
        summary.n_chunks            = segment.data_chunk_ptr_vec.size();
        summary.n_surfaces          = segment.dumped_surface_vec_ptr->size();

        if (segment.dumped_api_call_vec_ptr->empty() == false)
        {
            summary.first_call_argument = segment.dumped_api_call_vec_ptr->front().arg_in_vec.at(0).get_u32();
        }

        for (const auto& chunk_ptr : segment.data_chunk_ptr_vec)
        {
            summary.n_chunk_bytes += chunk_ptr->size();

            for (const uint8_t byte : *chunk_ptr)
            {
                summary.chunk_byte_sum += byte;
            }
        }

        result.segment_vec.push_back(summary);
    }

    if (reader_ptr != nullptr)
    {
        result.is_truncated = reader_ptr->is_truncated();
    }

    reader_ptr.reset();
    ::remove(Tests::WorkloadFileBuilder::get_filename_ptr() );

    return result;
}

TEST(WorkloadReaderThreads, ThreadsGiveTheSegmentsInTheOrderOfTheFile)
{
    constexpr uint32_t N_CALLS       = 50;
    constexpr size_t   N_CHUNK_BYTES = 600 * 1024;
    constexpr uint32_t N_SEGMENTS    = 12;

    std::vector<uint8_t> file_u8_vec;

    Tests::WorkloadFileBuilder::build_many_segments(&file_u8_vec,
                                                    N_SEGMENTS,
                                                    N_CALLS,
                                                    N_CHUNK_BYTES);

    for (const uint32_t n_threads : {1u, 2u, 5u})
    {
        Capture::APIDumpLoader::WorkloadReader::Options options;

        options.n_threads = n_threads;

        const auto reading = read_whole_file(file_u8_vec,
                                             options);

        ASSERT_EQ(reading.segment_vec.size(),
                  N_SEGMENTS) << n_threads << " threads";
        EXPECT_FALSE(reading.is_truncated);

        for (uint32_t n_segment = 0;
                      n_segment < N_SEGMENTS;
                    ++n_segment)
        {
            const auto& summary = reading.segment_vec.at(n_segment);

            /* Chunk IDs count across segments, whichever thread made a segment. */
            EXPECT_EQ(summary.first_data_chunk_id,
                      n_segment * Tests::WorkloadFileBuilder::N_CHUNKS_PER_SEGMENT);
            EXPECT_EQ(summary.first_call_argument,
                      n_segment * 1000u);
            EXPECT_EQ(summary.n_calls,
                      N_CALLS);
            EXPECT_EQ(summary.n_chunks,
                      Tests::WorkloadFileBuilder::N_CHUNKS_PER_SEGMENT);
            EXPECT_EQ(summary.n_chunk_bytes,
                      N_CHUNK_BYTES * Tests::WorkloadFileBuilder::N_CHUNKS_PER_SEGMENT);
        }
    }
}

TEST(WorkloadReaderThreads, ThreadsReadWhatTheSerialReaderReadsOfEveryKindOfFile)
{
    std::vector<std::vector<uint8_t> > file_u8_vec_vec(6);

    Tests::WorkloadFileBuilder::build_many_segments(&file_u8_vec_vec.at(0),
                                                    9,
                                                    20,
                                                    300 * 1024);
    Tests::WorkloadFileBuilder::build_two_segments (&file_u8_vec_vec.at(1) );
    Tests::WorkloadFileBuilder::build_two_segments (&file_u8_vec_vec.at(2),
                                                    2); /* ends in the middle of a chunk */
    Tests::WorkloadFileBuilder::build_two_segments (&file_u8_vec_vec.at(3) );
    Tests::WorkloadFileBuilder::build_large_chunk  (&file_u8_vec_vec.at(4) );
    Tests::WorkloadFileBuilder::build_large_chunk  (&file_u8_vec_vec.at(5) );

    /* The last frame is cut, a little is left of it. */
    file_u8_vec_vec.at(3).resize(file_u8_vec_vec.at(3).size() - 12);

    /* The file ends in the middle of a frame. */
    file_u8_vec_vec.at(4).resize(file_u8_vec_vec.at(4).size() / 2);

    /* Garbage in the place of the frames. */
    ::memset(file_u8_vec_vec.at(5).data() + sizeof(APIInterceptor::WorkloadFormat::WorkloadFileHeader),
             0xA5,
             file_u8_vec_vec.at(5).size() - sizeof(APIInterceptor::WorkloadFormat::WorkloadFileHeader) );

    for (size_t n_file = 0;
                n_file < file_u8_vec_vec.size();
              ++n_file)
    {
        Capture::APIDumpLoader::WorkloadReader::Options serial_options;
        Capture::APIDumpLoader::WorkloadReader::Options threaded_options;

        threaded_options.n_threads = 3;

        const auto serial_reading   = read_whole_file(file_u8_vec_vec.at(n_file),
                                                      serial_options);
        const auto threaded_reading = read_whole_file(file_u8_vec_vec.at(n_file),
                                                      threaded_options);

        EXPECT_EQ(threaded_reading.is_truncated,
                  serial_reading.is_truncated) << "file " << n_file;
        ASSERT_EQ(threaded_reading.segment_vec.size(),
                  serial_reading.segment_vec.size() ) << "file " << n_file;

        for (size_t n_segment = 0;
                    n_segment < serial_reading.segment_vec.size();
                  ++n_segment)
        {
            EXPECT_TRUE(threaded_reading.segment_vec.at(n_segment) == serial_reading.segment_vec.at(n_segment) )
                << "file " << n_file << ", segment " << n_segment;
        }
    }
}

TEST(WorkloadReaderThreads, OneSegmentInFlightIsEnough)
{
    std::vector<uint8_t> file_u8_vec;

    Tests::WorkloadFileBuilder::build_many_segments(&file_u8_vec,
                                                    6,
                                                    10,
                                                    100 * 1024);

    Capture::APIDumpLoader::WorkloadReader::Options options;

    options.n_segments_in_flight = 1;
    options.n_threads            = 4;

    EXPECT_EQ(read_whole_file(file_u8_vec,
                              options).segment_vec.size(),
              6u);
}

TEST(WorkloadReaderThreads, DataChunksAboveALimitAreLeftOutAndTheRestIsStillRead)
{
    std::vector<uint8_t> file_u8_vec;

    /* [2 calls, 2 chunks of 3 and 0 bytes, 1 surface] and [1 call, 1 chunk of 4 bytes]. */
    Tests::WorkloadFileBuilder::build_two_segments(&file_u8_vec);

    for (const uint32_t n_threads : {0u, 2u})
    {
        Capture::APIDumpLoader::WorkloadReader::Options options;
        Capture::APIDumpLoader::Workload                segment;

        options.n_threads                      = n_threads;
        options.skip_data_chunks_above_n_bytes = 2;

        Tests::WorkloadFileBuilder::write_file(file_u8_vec);

        auto reader_ptr = Capture::APIDumpLoader::WorkloadReader::create(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                                                         options);

        ASSERT_NE(reader_ptr,
                  nullptr);

        ASSERT_TRUE(reader_ptr->read_next_segment(&segment) );

        /* The chunks are all there, as many as the dump has, and the one which is above the limit is empty. */
        ASSERT_EQ(segment.data_chunk_ptr_vec.size(),
                  2u);
        EXPECT_TRUE(segment.data_chunk_ptr_vec.at(0)->empty() );
        EXPECT_TRUE(segment.data_chunk_ptr_vec.at(1)->empty() );

        /* What follows a chunk which was left out is where it should be. */
        ASSERT_EQ(segment.dumped_surface_vec_ptr->size(),
                  1u);
        EXPECT_EQ(segment.dumped_surface_vec_ptr->at(0).data_u8_vec.size(),
                  8u);
        EXPECT_EQ(segment.dumped_surface_vec_ptr->at(0).data_u8_vec.at(7),
                  8u);

        ASSERT_TRUE(reader_ptr->read_next_segment(&segment) );
        EXPECT_EQ(segment.first_data_chunk_id,
                  2u);
        ASSERT_EQ(segment.data_chunk_ptr_vec.size(),
                  1u);
        EXPECT_TRUE(segment.data_chunk_ptr_vec.at(0)->empty() );

        EXPECT_FALSE(reader_ptr->read_next_segment(&segment) );
        EXPECT_FALSE(reader_ptr->is_truncated() );

        reader_ptr.reset();
        ::remove(Tests::WorkloadFileBuilder::get_filename_ptr() );
    }
}

TEST(WorkloadReaderThreads, ChunksWhichAreLeftOutAreNotCopiedAnywhere)
{
    std::vector<uint8_t> file_u8_vec;

    Tests::WorkloadFileBuilder::build_many_segments(&file_u8_vec,
                                                    4,
                                                    5,
                                                    700 * 1024);

    Capture::APIDumpLoader::WorkloadReader::Options options;

    options.n_threads                      = 2;
    options.skip_data_chunks_above_n_bytes = 64 * 1024;

    const auto reading = read_whole_file(file_u8_vec,
                                         options);

    ASSERT_EQ(reading.segment_vec.size(),
              4u);

    for (uint32_t n_segment = 0;
                  n_segment < 4;
                ++n_segment)
    {
        EXPECT_EQ(reading.segment_vec.at(n_segment).n_chunks,
                  Tests::WorkloadFileBuilder::N_CHUNKS_PER_SEGMENT);
        EXPECT_EQ(reading.segment_vec.at(n_segment).n_chunk_bytes,
                  0u);
        EXPECT_EQ(reading.segment_vec.at(n_segment).first_data_chunk_id,
                  n_segment * Tests::WorkloadFileBuilder::N_CHUNKS_PER_SEGMENT);
        EXPECT_EQ(reading.segment_vec.at(n_segment).n_calls,
                  5u);
    }

    EXPECT_FALSE(reading.is_truncated);
}

TEST(WorkloadReaderThreads, ASegmentWhichCompressesWellIsRead)
{
    std::vector<uint8_t> file_u8_vec;

    /* Runs of one value: the frame is a tiny part of the segment. */
    Tests::WorkloadFileBuilder::build_many_segments(&file_u8_vec,
                                                    1,
                                                    1,
                                                    8 * 1024 * 1024);

    Capture::APIDumpLoader::WorkloadReader::Options options;

    const auto serial_reading = read_whole_file(file_u8_vec,
                                                options);

    ASSERT_EQ(serial_reading.segment_vec.size(),
              1u);
    EXPECT_EQ(serial_reading.segment_vec.at(0).n_chunk_bytes,
              2u * 8 * 1024 * 1024);
    EXPECT_FALSE(serial_reading.is_truncated);
}

TEST(WorkloadReaderThreads, AReaderCanBeLetGoOfBeforeTheFileIsRead)
{
    std::vector<uint8_t> file_u8_vec;

    Tests::WorkloadFileBuilder::build_many_segments(&file_u8_vec,
                                                    20,
                                                    10,
                                                    200 * 1024);
    Tests::WorkloadFileBuilder::write_file         (file_u8_vec);

    Capture::APIDumpLoader::WorkloadReader::Options options;
    Capture::APIDumpLoader::Workload                segment;

    options.n_threads = 4;

    auto reader_ptr = Capture::APIDumpLoader::WorkloadReader::create(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                                                     options);

    ASSERT_NE(reader_ptr,
              nullptr);
    ASSERT_TRUE(reader_ptr->read_next_segment(&segment) );

    /* The threads are busy with the segments to come; they must stop, and not wait for anybody to take them. */
    reader_ptr.reset();

    ::remove(Tests::WorkloadFileBuilder::get_filename_ptr() );
}

TEST(WorkloadReaderThreads, ChunksWhichOnlyUnwantedCallsReferToAreLeftOut)
{
    std::vector<uint8_t> file_u8_vec;

    /* Chunks 0 to 3 are of 1 to 4 bytes. Frame 0 refers to chunk 0, frame 1 to chunks 1 and 0, frame 2 to chunk 2; chunk 3 is referred to by none. */
    Tests::WorkloadFileBuilder::build_chunk_references(&file_u8_vec);

    for (const uint32_t n_threads : {0u, 2u})
    {
        for (const uint64_t wanted_frame_index : {1u, 99u})
        {
            Capture::APIDumpLoader::WorkloadReader::Options options;
            Capture::APIDumpLoader::WorkloadReader::SegmentStart start;
            Capture::APIDumpLoader::Workload                segment;

            start.file_offset_n_bytes = sizeof(APIInterceptor::WorkloadFormat::WorkloadFileHeader);

            options.chunk_wanted_func = [wanted_frame_index](const Capture::APIDumpLoader::DumpedAPICall&,
                                                             const uint64_t&                              in_frame_index)
                                        {
                                            return (in_frame_index == wanted_frame_index);
                                        };
            options.n_threads         = n_threads;

            options.segment_start_vec.push_back(start);

            Tests::WorkloadFileBuilder::write_file(file_u8_vec);

            auto reader_ptr = Capture::APIDumpLoader::WorkloadReader::create(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                                                             options);

            ASSERT_NE(reader_ptr,
                      nullptr);
            ASSERT_TRUE(reader_ptr->read_next_segment(&segment) );
            ASSERT_EQ(segment.data_chunk_ptr_vec.size(),
                      4u);

            /* A chunk which a wanted call refers to is read, whoever else refers to it; the numbers of the chunks stay. */
            EXPECT_EQ(segment.data_chunk_ptr_vec.at(0)->size(),
                      (wanted_frame_index == 1) ? 1u : 0u);
            EXPECT_EQ(segment.data_chunk_ptr_vec.at(1)->size(),
                      (wanted_frame_index == 1) ? 2u : 0u);
            EXPECT_EQ(segment.data_chunk_ptr_vec.at(2)->size(),
                      0u);
            EXPECT_EQ(segment.data_chunk_ptr_vec.at(3)->size(),
                      4u);

            reader_ptr.reset();
            ::remove(Tests::WorkloadFileBuilder::get_filename_ptr() );
        }
    }
}

TEST(WorkloadReaderThreads, ASegmentWhichTheIndexDoesNotHaveIsReadInFull)
{
    std::vector<uint8_t> file_u8_vec;

    Tests::WorkloadFileBuilder::build_chunk_references(&file_u8_vec);

    Capture::APIDumpLoader::WorkloadReader::Options options;
    Capture::APIDumpLoader::Workload                segment;

    options.chunk_wanted_func = [](const Capture::APIDumpLoader::DumpedAPICall&,
                                   const uint64_t&)
                                {
                                    return false;
                                };

    Tests::WorkloadFileBuilder::write_file(file_u8_vec);

    auto reader_ptr = Capture::APIDumpLoader::WorkloadReader::create(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                                                     options);

    ASSERT_NE(reader_ptr,
              nullptr);
    ASSERT_TRUE(reader_ptr->read_next_segment(&segment) );

    for (size_t n_chunk = 0;
                n_chunk < segment.data_chunk_ptr_vec.size();
              ++n_chunk)
    {
        EXPECT_EQ(segment.data_chunk_ptr_vec.at(n_chunk)->size(),
                  n_chunk + 1);
    }

    reader_ptr.reset();
    ::remove(Tests::WorkloadFileBuilder::get_filename_ptr() );
}

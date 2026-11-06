/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the comparison of two workloads: what each holds, and where their calls first differ.
 */
#include <gtest/gtest.h>
#include "Capture/APIDumpLoader/workload_comparison.h"
#include "workload_file_builder.h"
#include <stdio.h>

namespace
{
    constexpr uint32_t N_CALLS_PER_SEGMENT = 7;
    constexpr uint32_t N_SEGMENTS          = 6;

    /* Two workload files, which are removed with this. */
    class TwoFiles
    {
    public:
        TwoFiles(const std::vector<uint8_t>& in_first_u8_vec,
                 const std::vector<uint8_t>& in_second_u8_vec)
        {
            Tests::WorkloadFileBuilder::write_file(in_first_u8_vec);

            FILE* const file_handle = ::fopen(get_second_filename_ptr(),
                                              "wb");

            if (file_handle != nullptr)
            {
                ::fwrite(in_second_u8_vec.data(),
                         in_second_u8_vec.size(),
                         1,
                         file_handle);
                ::fclose(file_handle);
            }
        }

        ~TwoFiles()
        {
            ::remove(Tests::WorkloadFileBuilder::get_filename_ptr() );
            ::remove(get_second_filename_ptr() );
        }

        static const char* get_second_filename_ptr()
        {
            return "second_comparison_test.workload";
        }
    };

    std::vector<uint8_t> make_file(const uint32_t& in_n_segments,
                                   const uint32_t& in_n_calls_per_frame)
    {
        std::vector<uint8_t> result_u8_vec;

        Tests::WorkloadFileBuilder::build_segments(&result_u8_vec,
                                                   in_n_segments,
                                                   N_CALLS_PER_SEGMENT,
                                                   in_n_calls_per_frame);

        return result_u8_vec;
    }
}

TEST(WorkloadComparer, AWorkloadIsTheSameAsItself)
{
    TwoFiles                                     files(make_file(N_SEGMENTS, 4),
                                                       make_file(N_SEGMENTS, 4) );
    Capture::APIDumpLoader::WorkloadComparison   comparison;
    std::string                                  error;

    ASSERT_TRUE(Capture::APIDumpLoader::WorkloadComparer::compare(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                                                  TwoFiles::get_second_filename_ptr(),
                                                                  0,
                                                                 &comparison,
                                                                 &error) ) << error;

    EXPECT_TRUE(comparison.has_same_call_sequence);
    EXPECT_EQ(comparison.first.n_calls,
              static_cast<uint64_t>(N_SEGMENTS * N_CALLS_PER_SEGMENT) );
    EXPECT_EQ(comparison.first.n_calls,
              comparison.second.n_calls);
    EXPECT_EQ(comparison.first.n_frames,
              8u);
    EXPECT_EQ(comparison.first.n_chunks,
              static_cast<uint64_t>(N_SEGMENTS) );
    EXPECT_EQ(comparison.first.call_count_map,
              comparison.second.call_count_map);
    EXPECT_EQ(comparison.first.pointer_n_bytes,
              Tests::WorkloadFileBuilder::POINTER_N_BYTES);
}

TEST(WorkloadComparer, TheFirstCallOfAnotherFunctionIsWhereTheyDifferWithItsFrame)
{
    /* The frames of the one end at every fifth call, and the frames of the other at every fourth. */
    TwoFiles                                     files(make_file(N_SEGMENTS, 4),
                                                       make_file(N_SEGMENTS, 3) );
    Capture::APIDumpLoader::WorkloadComparison   comparison;
    std::string                                  error;

    ASSERT_TRUE(Capture::APIDumpLoader::WorkloadComparer::compare(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                                                  TwoFiles::get_second_filename_ptr(),
                                                                  0,
                                                                 &comparison,
                                                                 &error) ) << error;

    EXPECT_FALSE(comparison.has_same_call_sequence);
    EXPECT_EQ(comparison.first_difference_call_index,
              3u);
    EXPECT_EQ(comparison.first_difference_frame_index,
              0u);
    EXPECT_EQ(comparison.first_difference_first_function,
              APIInterceptor::APIFUNCTION_GDI32_GETPIXELFORMAT);
    EXPECT_EQ(comparison.first_difference_second_function,
              APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS);
    EXPECT_EQ(comparison.first.n_frames,
              8u);
    EXPECT_EQ(comparison.second.n_frames,
              10u);
}

TEST(WorkloadComparer, AWorkloadWhichEndsFirstDiffersWhereItEnds)
{
    TwoFiles                                     files(make_file(N_SEGMENTS, 4),
                                                       make_file(N_SEGMENTS - 2, 4) );
    Capture::APIDumpLoader::WorkloadComparison   comparison;
    std::string                                  error;

    ASSERT_TRUE(Capture::APIDumpLoader::WorkloadComparer::compare(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                                                  TwoFiles::get_second_filename_ptr(),
                                                                  0,
                                                                 &comparison,
                                                                 &error) ) << error;

    EXPECT_FALSE(comparison.has_same_call_sequence);
    EXPECT_EQ(comparison.first_difference_call_index,
              static_cast<uint64_t>( (N_SEGMENTS - 2) * N_CALLS_PER_SEGMENT) );
    EXPECT_EQ(comparison.first_difference_second_function,
              APIInterceptor::APIFUNCTION_UNKNOWN);
    EXPECT_EQ(comparison.first.n_calls,
              static_cast<uint64_t>(N_SEGMENTS * N_CALLS_PER_SEGMENT) );
    EXPECT_EQ(comparison.second.n_calls,
              static_cast<uint64_t>( (N_SEGMENTS - 2) * N_CALLS_PER_SEGMENT) );
}

TEST(WorkloadComparer, AFileThatCannotBeOpenedIsNamedInTheError)
{
    Capture::APIDumpLoader::WorkloadComparison   comparison;
    std::string                                  error;

    EXPECT_FALSE(Capture::APIDumpLoader::WorkloadComparer::compare("no_such_workload.workload",
                                                                   "no_such_workload_either.workload",
                                                                   0,
                                                                  &comparison,
                                                                  &error) );
    EXPECT_NE(error.find("no_such_workload.workload"),
              std::string::npos);
}

/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Tests for ReplayCoverage, which says from a workload alone what a replay of it would fail on, and for the executors' answers that it is built on.
 */
#include <gtest/gtest.h>
#include "d3d7_call_executor.h"
#include "d3d8_call_executor.h"
#include "gl_call_executor.h"
#include "null_call_executor.h"
#include "object_remapper.h"
#include "replay_coverage.h"
#include "win32_call_executor.h"

namespace
{
    /* What the replay does with the functions of the tests: GL's glAccum is replayed, a window is not (it has no code), and the start of DirectDraw
     * is left out.
     */
    Replay::ReplayEngineDLL::CallSupport get_test_support(const APIInterceptor::APIFunction& in_function)
    {
        Replay::ReplayEngineDLL::CallSupport result = Replay::ReplayEngineDLL::CallSupport::REPLAYED;

        switch (in_function)
        {
            case APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATE:
            {
                result = Replay::ReplayEngineDLL::CallSupport::SKIPPED;

                break;
            }

            case APIInterceptor::APIFUNCTION_USER32_CREATEWINDOWEXA:
            {
                result = Replay::ReplayEngineDLL::CallSupport::UNSUPPORTED;

                break;
            }

            default:
            {
                break;
            }
        }

        return result;
    }

    /* A segment of calls of the functions, with one chunk of data (the one with the ID that the segment starts at). */
    Capture::APIDumpLoader::Workload make_segment(const std::vector<APIInterceptor::APIFunction>& in_function_vec,
                                                  const uint32_t&                                  in_first_data_chunk_id)
    {
        Capture::APIDumpLoader::Workload result;

        result.dumped_api_call_vec_ptr = std::make_unique<Capture::APIDumpLoader::DumpedAPICallVector>();
        result.first_data_chunk_id     = in_first_data_chunk_id;
        result.pointer_n_bytes         = 4;

        result.data_chunk_ptr_vec.push_back(std::make_unique<Capture::APIDumpLoader::DataChunk>(4) );

        for (const auto function : in_function_vec)
        {
            Capture::APIDumpLoader::DumpedAPICall call;

            call.func = function;

            result.dumped_api_call_vec_ptr->push_back(std::move(call) );
        }

        return result;
    }
}

TEST(ReplayCoverage, TheFunctionsThatAreNotReplayedAreCountedWithWhereTheyFirstAre)
{
    Replay::ReplayEngineDLL::ReplayCoverage coverage(get_test_support);

    coverage.add_segment(make_segment({APIInterceptor::APIFUNCTION_GL_GLACCUM,
                                       APIInterceptor::APIFUNCTION_USER32_CREATEWINDOWEXA,
                                       APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS,
                                       APIInterceptor::APIFUNCTION_USER32_CREATEWINDOWEXA,
                                       APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATE},
                                      0) );
    coverage.add_segment(make_segment({APIInterceptor::APIFUNCTION_USER32_CREATEWINDOWEXA},
                                      1) );

    const auto report = coverage.get_report();

    EXPECT_EQ(report.n_calls,
              6u);
    EXPECT_EQ(report.n_frames,
              1u);
    EXPECT_EQ(report.n_unsupported_calls,
              3u);
    EXPECT_EQ(report.n_skipped_calls,
              1u);
    EXPECT_EQ(report.pointer_n_bytes,
              4u);

    ASSERT_EQ(report.function_entry_vec.size(),
              2u);

    /* In the order of the enum: the DirectDraw function is after the window one. */
    const auto& window_entry = (report.function_entry_vec.at(0).function == APIInterceptor::APIFUNCTION_USER32_CREATEWINDOWEXA) ? report.function_entry_vec.at(0)
                                                                                                                                  : report.function_entry_vec.at(1);

    EXPECT_EQ(window_entry.n_calls,
              3u);
    EXPECT_EQ(window_entry.first_call_index,
              1u);
    EXPECT_EQ(window_entry.first_frame_index,
              0u);
    EXPECT_EQ(window_entry.support,
              Replay::ReplayEngineDLL::CallSupport::UNSUPPORTED);
    EXPECT_FALSE(Replay::ReplayEngineDLL::ReplayCoverage::is_replayable(report) );
}

TEST(ReplayCoverage, ACallThatIsOnlyLeftOutDoesNotStopAReplay)
{
    Replay::ReplayEngineDLL::ReplayCoverage coverage(get_test_support);

    coverage.add_segment(make_segment({APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATE,
                                       APIInterceptor::APIFUNCTION_GL_GLACCUM},
                                      0) );

    const auto report = coverage.get_report();

    EXPECT_EQ(report.n_skipped_calls,
              1u);
    EXPECT_TRUE(Replay::ReplayEngineDLL::ReplayCoverage::is_replayable(report) );
}

TEST(ReplayCoverage, AChunkWhichIsNotInTheSegmentIsMissingWithTheCallThatReferToItGiven)
{
    Replay::ReplayEngineDLL::ReplayCoverage coverage(get_test_support);
    auto                                    segment = make_segment({APIInterceptor::APIFUNCTION_GL_GLACCUM,
                                                                    APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS,
                                                                    APIInterceptor::APIFUNCTION_GL_GLACCUM,
                                                                    APIInterceptor::APIFUNCTION_GL_GLACCUM},
                                                                   10);

    /* The chunk of the segment is 10: the first call has it, the third refers to 11 (there is no such chunk), the fourth to 9 (it is of an earlier segment). */
    segment.dumped_api_call_vec_ptr->at(0).arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_data_chunk_id(10) );
    segment.dumped_api_call_vec_ptr->at(2).arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_data_chunk_id(11) );
    segment.dumped_api_call_vec_ptr->at(3).arg_out_vec.push_back(APIInterceptor::APIFunctionArgument::create_data_chunk_id(9) );

    coverage.add_segment(segment);

    const auto report = coverage.get_report();

    EXPECT_EQ(report.n_missing_chunk_references,
              2u);
    EXPECT_EQ(report.first_missing_chunk_call_index,
              2u);
    EXPECT_EQ(report.first_missing_chunk_frame_index,
              1u);
    EXPECT_EQ(report.first_missing_chunk_function,
              APIInterceptor::APIFUNCTION_GL_GLACCUM);
    EXPECT_FALSE(Replay::ReplayEngineDLL::ReplayCoverage::is_replayable(report) );
}

TEST(CallSupport, TheExecutorsSayWhatTheyReplayLeaveOutAndFailOn)
{
    Replay::ReplayEngineDLL::ObjectRemapper remapper;
    Replay::ReplayEngineDLL::D3D7CallExecutor d3d7_executor(&remapper);
    Replay::ReplayEngineDLL::D3D8CallExecutor d3d8_executor(&remapper);
    Replay::ReplayEngineDLL::GlCallExecutor   gl_executor  (&remapper);
    Replay::ReplayEngineDLL::NullCallExecutor null_executor;
    Replay::ReplayEngineDLL::Win32CallExecutor win32_executor(&remapper,
                                                              []() {},
                                                              [](const Replay::ReplayEngineDLL::WindowPlacement&) {});

    /* A method that the replay has code for; one that only asks about the API; and one that no executor of the API knows. */
    EXPECT_EQ(d3d7_executor.get_call_support(APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW7_CREATESURFACE),
              Replay::ReplayEngineDLL::CallSupport::REPLAYED);
    EXPECT_EQ(d3d7_executor.get_call_support(APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW7_ENUMDISPLAYMODES),
              Replay::ReplayEngineDLL::CallSupport::SKIPPED);
    EXPECT_EQ(d3d8_executor.get_call_support(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT),
              Replay::ReplayEngineDLL::CallSupport::REPLAYED);
    EXPECT_EQ(gl_executor.get_call_support(APIInterceptor::APIFUNCTION_GL_GLACCUM),
              Replay::ReplayEngineDLL::CallSupport::REPLAYED);
    EXPECT_EQ(gl_executor.get_call_support(APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS),
              Replay::ReplayEngineDLL::CallSupport::UNSUPPORTED);
    EXPECT_EQ(win32_executor.get_call_support(APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS),
              Replay::ReplayEngineDLL::CallSupport::REPLAYED);
    EXPECT_EQ(win32_executor.get_call_support(APIInterceptor::APIFUNCTION_GL_GLACCUM),
              Replay::ReplayEngineDLL::CallSupport::UNSUPPORTED);
    EXPECT_EQ(null_executor.get_call_support(APIInterceptor::APIFUNCTION_GL_GLACCUM),
              Replay::ReplayEngineDLL::CallSupport::SKIPPED);
}

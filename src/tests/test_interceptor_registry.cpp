/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks that a call interceptor is given only the calls of the APIs it names.
 */
#include <gtest/gtest.h>
#include "capture/api_dump_loader/api_info.h"
#include "replay/replay_engine_dll/entrypoints.h"
#include "replay/replay_engine_dll/interceptor_registry.h"
#include "workload_file_builder.h"
#include <algorithm>
#include <atomic>
#include <chrono>
#include <thread>

namespace
{
    using Capture::APIDumpLoader::APIGroup;

    /* Counts the calls it is asked about, and names the APIs it wants (none: all). */
    class CountingInterceptor : public Replay::ReplayEngineDLL::ICallInterceptor
    {
    public:
        explicit CountingInterceptor(const std::vector<APIGroup>& in_group_vec = std::vector<APIGroup>() )
            :m_group_vec(in_group_vec)
        {
            /* Stub */
        }

        std::vector<APIGroup> get_api_groups() const override
        {
            return m_group_vec;
        }

        void on_call_replayed(const Capture::APIDumpLoader::DumpedAPICall&,
                              const uint32_t&,
                              const bool&) override
        {
            /* Stub */
        }

        bool should_execute_call(const Capture::APIDumpLoader::DumpedAPICall&,
                                 const uint32_t&) override
        {
            n_calls_asked++;

            return true;
        }

        std::atomic<uint32_t> n_calls_asked {0};

    private:
        std::vector<APIGroup> m_group_vec;
    };

    bool has_interceptor(const std::vector<Replay::ReplayEngineDLL::ICallInterceptor*>& in_interceptor_ptr_vec,
                         const Replay::ReplayEngineDLL::ICallInterceptor*               in_interceptor_ptr)
    {
        return (std::find(in_interceptor_ptr_vec.begin(),
                          in_interceptor_ptr_vec.end  (),
                          in_interceptor_ptr) != in_interceptor_ptr_vec.end() );
    }
}

TEST(InterceptorRegistry, AnInterceptorThatNamesAnApiIsGivenThatApiAndNoOther)
{
    Replay::ReplayEngineDLL::InterceptorRegistry registry;
    CountingInterceptor                          interceptor({APIGroup::GL, APIGroup::WGL});

    registry.add(&interceptor);

    EXPECT_TRUE (has_interceptor(registry.get_interceptor_ptr_vec(APIGroup::GL),
                                &interceptor) );
    EXPECT_TRUE (has_interceptor(registry.get_interceptor_ptr_vec(APIGroup::WGL),
                                &interceptor) );
    EXPECT_FALSE(has_interceptor(registry.get_interceptor_ptr_vec(APIGroup::D3D7),
                                &interceptor) );
    EXPECT_FALSE(has_interceptor(registry.get_interceptor_ptr_vec(APIGroup::D3D8),
                                &interceptor) );
    EXPECT_FALSE(has_interceptor(registry.get_interceptor_ptr_vec(APIGroup::GDI32),
                                &interceptor) );
}

TEST(InterceptorRegistry, AnInterceptorThatNamesNoApiIsGivenAllOfThem)
{
    Replay::ReplayEngineDLL::InterceptorRegistry registry;
    CountingInterceptor                          interceptor;

    registry.add(&interceptor);

    for (const auto& group : Capture::APIDumpLoader::get_api_groups() )
    {
        EXPECT_TRUE(has_interceptor(registry.get_interceptor_ptr_vec(group),
                                   &interceptor) );
    }

    EXPECT_TRUE(has_interceptor(registry.get_interceptor_ptr_vec(APIGroup::UNKNOWN),
                               &interceptor) );
}

TEST(InterceptorRegistry, InterceptorsComeInTheOrderTheyWereAddedAndOneThatNamesAnApiTwiceIsListedOnce)
{
    Replay::ReplayEngineDLL::InterceptorRegistry registry;
    CountingInterceptor                          first ({APIGroup::D3D8, APIGroup::D3D8});
    CountingInterceptor                          second({APIGroup::D3D8});

    registry.add(&first);
    registry.add(&second);

    const auto& interceptor_ptr_vec = registry.get_interceptor_ptr_vec(APIGroup::D3D8);

    ASSERT_EQ(interceptor_ptr_vec.size(),
              2u);
    EXPECT_EQ(interceptor_ptr_vec.at(0),
              &first);
    EXPECT_EQ(interceptor_ptr_vec.at(1),
              &second);
}

TEST(InterceptorRegistry, AListThatWasTakenStaysValidWhenAnInterceptorIsRemoved)
{
    Replay::ReplayEngineDLL::InterceptorRegistry registry;
    CountingInterceptor                          interceptor({APIGroup::GL});

    registry.add(&interceptor);

    const auto& list_before = registry.get_interceptor_ptr_vec(APIGroup::GL);

    registry.remove(&interceptor);

    EXPECT_EQ(list_before.size(),
              1u);
    EXPECT_TRUE(registry.get_interceptor_ptr_vec(APIGroup::GL).empty() );
}

TEST(InterceptorRegistry, TheEngineAsksAnInterceptorAboutTheCallsOfItsApisOnly)
{
    constexpr uint32_t N_CALLS_PER_FRAME = 2;
    constexpr uint32_t N_FRAMES          = 3;

    std::vector<uint8_t> file_u8_vec;

    /* Each frame: two calls and a SwapBuffers call, all of GDI32. */
    Tests::WorkloadFileBuilder::build_frames(&file_u8_vec,
                                             N_FRAMES,
                                             N_CALLS_PER_FRAME);
    Tests::WorkloadFileBuilder::write_file  (file_u8_vec);

    auto* const engine_ptr = Replay::ReplayEngineDLL::aiCreateReplayEngine();

    CountingInterceptor everything;
    CountingInterceptor gdi_only({APIGroup::GDI32});
    CountingInterceptor gl_only ({APIGroup::GL});
    CountingInterceptor d3d_only({APIGroup::D3D7, APIGroup::D3D8});

    ASSERT_TRUE(engine_ptr->load(Tests::WorkloadFileBuilder::get_filename_ptr(),
                                 nullptr) );

    engine_ptr->add_call_interceptor(&everything);
    engine_ptr->add_call_interceptor(&gdi_only);
    engine_ptr->add_call_interceptor(&gl_only);
    engine_ptr->add_call_interceptor(&d3d_only);

    auto* const controller_ptr = engine_ptr->get_playback_controller_ptr();

    controller_ptr->play();

    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(10);

    while (controller_ptr->get_status().state != Replay::ReplayEngineDLL::PlaybackState::FINISHED &&
           std::chrono::steady_clock::now()   <  deadline)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1) );
    }

    EXPECT_EQ(controller_ptr->get_status().state,
              Replay::ReplayEngineDLL::PlaybackState::FINISHED);
    EXPECT_EQ(everything.n_calls_asked.load(),
              N_FRAMES * (N_CALLS_PER_FRAME + 1) );
    EXPECT_EQ(gdi_only.n_calls_asked.load(),
              N_FRAMES * (N_CALLS_PER_FRAME + 1) );
    EXPECT_EQ(gl_only.n_calls_asked.load(),
              0u);
    EXPECT_EQ(d3d_only.n_calls_asked.load(),
              0u);

    engine_ptr->remove_call_interceptor(&everything);
    engine_ptr->remove_call_interceptor(&gdi_only);
    engine_ptr->remove_call_interceptor(&gl_only);
    engine_ptr->remove_call_interceptor(&d3d_only);

    Replay::ReplayEngineDLL::aiDestroyReplayEngine(engine_ptr);

    ::remove(Tests::WorkloadFileBuilder::get_filename_ptr() );
}

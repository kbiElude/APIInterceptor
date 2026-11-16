/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Tests for the device contexts of the windows that the replay makes: a window whose class owns its DC keeps it when the program releases it, and
 * the program may go on using it (an OpenGL demo swaps the buffers of a DC that it has released).
 */
#include <gtest/gtest.h>
#include "map_chunk_source.h"
#include "object_remapper.h"
#include "win32_call_executor.h"

namespace
{
    constexpr uint64_t DUMPED_HDC  = 0x6d010663;
    constexpr uint64_t DUMPED_HWND = 0x2102d0;
    constexpr uint32_t POPUP_STYLE = 0x80000000; /* WS_POPUP: no caption, not visible, so no window is shown */

    Capture::APIDumpLoader::DumpedAPICall make_call(const APIInterceptor::APIFunction& in_function)
    {
        Capture::APIDumpLoader::DumpedAPICall result;

        result.func = in_function;

        return result;
    }
}

TEST(Win32CallExecutor, ADcOfAWindowThatOwnsItsDcIsStillKnownAfterTheProgramReleasesIt)
{
    constexpr uint32_t WINDOW_NAME_CHUNK_ID = 1;

    Replay::ReplayEngineDLL::ObjectRemapper    remapper;
    Replay::ReplayEngineDLL::Win32CallExecutor executor(&remapper,
                                                        []() {},
                                                        [](const Replay::ReplayEngineDLL::WindowPlacement&) {});
    Tests::MapChunkSource                      source;
    std::string                                error;

    source.chunk_map[WINDOW_NAME_CHUNK_ID] = Capture::APIDumpLoader::DataChunk();

    auto create_call = make_call(APIInterceptor::APIFUNCTION_USER32_CREATEWINDOWEXA);

    create_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_u32(0) );
    create_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_void_ptr(nullptr) ); /* the replay's own class */
    create_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_data_chunk_id(WINDOW_NAME_CHUNK_ID) );
    create_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_u32(POPUP_STYLE) );
    create_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_u32(0) );
    create_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_u32(0) );
    create_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_u32(64) );
    create_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_u32(64) );
    create_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_void_ptr(nullptr) );
    create_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_void_ptr(nullptr) );
    create_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_void_ptr(nullptr) );
    create_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_void_ptr(nullptr) );
    create_call.returned_value_ptr.reset(new APIInterceptor::APIFunctionArgument(APIInterceptor::APIFunctionArgument::create_void_ptr(reinterpret_cast<void*>(DUMPED_HWND) ) ) );

    auto get_dc_call = make_call(APIInterceptor::APIFUNCTION_USER32_GETDC);

    get_dc_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_void_ptr(reinterpret_cast<void*>(DUMPED_HWND) ) );
    get_dc_call.returned_value_ptr.reset(new APIInterceptor::APIFunctionArgument(APIInterceptor::APIFunctionArgument::create_void_ptr(reinterpret_cast<void*>(DUMPED_HDC) ) ) );

    auto release_call = make_call(APIInterceptor::APIFUNCTION_USER32_RELEASEDC);

    release_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_void_ptr(reinterpret_cast<void*>(DUMPED_HWND) ) );
    release_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_void_ptr(reinterpret_cast<void*>(DUMPED_HDC) ) );

    ASSERT_TRUE(executor.execute(create_call,
                                 source,
                                &error) ) << error;
    ASSERT_TRUE(executor.execute(get_dc_call,
                                 source,
                                &error) ) << error;

    uint64_t live_hdc = 0;

    ASSERT_TRUE(remapper.get(Replay::ReplayEngineDLL::ObjectKind::HDC,
                             DUMPED_HDC,
                            &live_hdc) );
    EXPECT_NE(live_hdc,
              0u);

    ASSERT_TRUE(executor.execute(release_call,
                                 source,
                                &error) ) << error;

    uint64_t live_hdc_after = 0;

    EXPECT_TRUE(remapper.get(Replay::ReplayEngineDLL::ObjectKind::HDC,
                             DUMPED_HDC,
                            &live_hdc_after) );
    EXPECT_EQ(live_hdc_after,
              live_hdc);

    executor.shutdown();
}

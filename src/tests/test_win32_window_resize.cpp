/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Tests for the windows that the replay resizes as the program did (SetWindowPos and MoveWindow): the dump says the area for drawing the window had after the
 * call, and the replay's window gets that area, whatever frame it has.
 */
#include <gtest/gtest.h>
#include "map_chunk_source.h"
#include "object_remapper.h"
#include "win32_call_executor.h"

namespace
{
    constexpr uint64_t DUMPED_HWND = 0x2102d0;
    constexpr uint32_t POPUP_STYLE = 0x80000000; /* WS_POPUP: no frame */

    Capture::APIDumpLoader::DumpedAPICall make_call(const APIInterceptor::APIFunction& in_function)
    {
        Capture::APIDumpLoader::DumpedAPICall result;

        result.func = in_function;

        return result;
    }

    Capture::APIDumpLoader::DumpedAPICall make_create_call(const uint32_t& in_style,
                                                           const uint32_t& in_width,
                                                           const uint32_t& in_height)
    {
        constexpr uint32_t WINDOW_NAME_CHUNK_ID = 1;

        auto result = make_call(APIInterceptor::APIFUNCTION_USER32_CREATEWINDOWEXA);

        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_u32(0) );
        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_void_ptr(nullptr) ); /* the replay's own class */
        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_data_chunk_id(WINDOW_NAME_CHUNK_ID) );
        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_u32(in_style) );
        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_u32(0) );
        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_u32(0) );
        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_u32(in_width) );
        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_u32(in_height) );
        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_void_ptr(nullptr) );
        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_void_ptr(nullptr) );
        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_void_ptr(nullptr) );
        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_void_ptr(nullptr) );
        result.returned_value_ptr.reset(new APIInterceptor::APIFunctionArgument(APIInterceptor::APIFunctionArgument::create_void_ptr(reinterpret_cast<void*>(DUMPED_HWND) ) ) );

        return result;
    }

    /* The area for drawing the window had after the call follows the arguments of the call, in the output arguments (see the hook). in_has_client says whether the
     * dump has it.
     */
    void add_client_size(const int&                             in_client_width,
                         const int&                             in_client_height,
                         const bool&                            in_has_client,
                         Capture::APIDumpLoader::DumpedAPICall* inout_call_ptr)
    {
        inout_call_ptr->arg_out_vec = inout_call_ptr->arg_in_vec;

        if (in_has_client)
        {
            inout_call_ptr->arg_out_vec.push_back(APIInterceptor::APIFunctionArgument::create_i32(in_client_width) );
            inout_call_ptr->arg_out_vec.push_back(APIInterceptor::APIFunctionArgument::create_i32(in_client_height) );
        }
    }

    Capture::APIDumpLoader::DumpedAPICall make_set_window_pos_call(const uint64_t& in_dumped_window,
                                                                   const int&      in_client_width,
                                                                   const int&      in_client_height,
                                                                   const uint32_t& in_flags,
                                                                   const bool&     in_has_client)
    {
        auto result = make_call(APIInterceptor::APIFUNCTION_USER32_SETWINDOWPOS);

        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_void_ptr(reinterpret_cast<void*>(in_dumped_window) ) );
        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_void_ptr(nullptr) ); /* hWndInsertAfter */
        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_i32(0) );
        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_i32(0) );
        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_i32(646) ); /* the outer size is not what the replay goes by */
        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_i32(509) );
        result.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_u32(in_flags) );

        add_client_size(in_client_width,
                        in_client_height,
                        in_has_client,
                       &result);

        return result;
    }

    /* The size of the area for drawing of the window that the replay made for the dumped window. */
    SIZE get_client_size(Replay::ReplayEngineDLL::ObjectRemapper* in_remapper_ptr)
    {
        RECT     client    = {};
        uint64_t live_hwnd = 0;

        in_remapper_ptr->get(Replay::ReplayEngineDLL::ObjectKind::HWND,
                             DUMPED_HWND,
                            &live_hwnd);

        ::GetClientRect(reinterpret_cast<HWND>(live_hwnd),
                       &client);

        return SIZE{client.right  - client.left,
                    client.bottom - client.top};
    }
}

TEST(Win32WindowResize, SetWindowPosGivesAWindowWithoutAFrameTheAreaTheProgramsWindowHad)
{
    Replay::ReplayEngineDLL::ObjectRemapper    remapper;
    Replay::ReplayEngineDLL::Win32CallExecutor executor(&remapper,
                                                        []() {},
                                                        [](const Replay::ReplayEngineDLL::WindowPlacement&) {});
    Tests::MapChunkSource                      source;
    std::string                                error;

    executor.set_windows_visible(false);

    source.chunk_map[1] = Capture::APIDumpLoader::DataChunk();

    ASSERT_TRUE(executor.execute(make_create_call(POPUP_STYLE,
                                                  64,
                                                  64),
                                 source,
                                &error) ) << error;
    ASSERT_TRUE(executor.execute(make_set_window_pos_call(DUMPED_HWND,
                                                          200,
                                                          120,
                                                          0, /* flags */
                                                          true /* in_has_client */),
                                 source,
                                &error) ) << error;

    const SIZE client = get_client_size(&remapper);

    EXPECT_EQ(client.cx,
              200);
    EXPECT_EQ(client.cy,
              120);

    executor.shutdown();
}

TEST(Win32WindowResize, TheAreaForDrawingOfAWindowWithAFrameIsTheOneTheDumpSaysWhateverTheFrame)
{
    constexpr int CLIENT_HEIGHT = 480;
    constexpr int CLIENT_WIDTH  = 640;

    Replay::ReplayEngineDLL::ObjectRemapper    remapper;
    Replay::ReplayEngineDLL::Win32CallExecutor executor(&remapper,
                                                        []() {},
                                                        [](const Replay::ReplayEngineDLL::WindowPlacement&) {});
    Tests::MapChunkSource                      source;
    std::string                                error;

    executor.set_windows_visible(false);

    source.chunk_map[1] = Capture::APIDumpLoader::DataChunk();

    ASSERT_TRUE(executor.execute(make_create_call(WS_OVERLAPPEDWINDOW,
                                                  380,
                                                  400),
                                 source,
                                &error) ) << error;
    ASSERT_TRUE(executor.execute(make_set_window_pos_call(DUMPED_HWND,
                                                          CLIENT_WIDTH,
                                                          CLIENT_HEIGHT,
                                                          0, /* flags */
                                                          true /* in_has_client */),
                                 source,
                                &error) ) << error;

    const SIZE client = get_client_size(&remapper);

    EXPECT_EQ(client.cx,
              CLIENT_WIDTH);
    EXPECT_EQ(client.cy,
              CLIENT_HEIGHT);

    executor.shutdown();
}

TEST(Win32WindowResize, MoveWindowResizesLikeSetWindowPos)
{
    Replay::ReplayEngineDLL::ObjectRemapper    remapper;
    Replay::ReplayEngineDLL::Win32CallExecutor executor(&remapper,
                                                        []() {},
                                                        [](const Replay::ReplayEngineDLL::WindowPlacement&) {});
    Tests::MapChunkSource                      source;
    std::string                                error;

    executor.set_windows_visible(false);

    source.chunk_map[1] = Capture::APIDumpLoader::DataChunk();

    auto move_call = make_call(APIInterceptor::APIFUNCTION_USER32_MOVEWINDOW);

    move_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_void_ptr(reinterpret_cast<void*>(DUMPED_HWND) ) );
    move_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_i32(10) );
    move_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_i32(20) );
    move_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_i32(306) );
    move_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_i32(179) );
    move_call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_i32(1) );

    add_client_size(300,
                    150,
                    true, /* in_has_client */
                   &move_call);

    ASSERT_TRUE(executor.execute(make_create_call(POPUP_STYLE,
                                                  64,
                                                  64),
                                 source,
                                &error) ) << error;
    ASSERT_TRUE(executor.execute(move_call,
                                 source,
                                &error) ) << error;

    const SIZE client = get_client_size(&remapper);

    EXPECT_EQ(client.cx,
              300);
    EXPECT_EQ(client.cy,
              150);

    executor.shutdown();
}

TEST(Win32WindowResize, ACallThatKeepsTheSizeLeavesTheWindowAlone)
{
    constexpr uint32_t SWP_NOSIZE_FLAG = 0x0001;

    Replay::ReplayEngineDLL::ObjectRemapper    remapper;
    Replay::ReplayEngineDLL::Win32CallExecutor executor(&remapper,
                                                        []() {},
                                                        [](const Replay::ReplayEngineDLL::WindowPlacement&) {});
    Tests::MapChunkSource                      source;
    std::string                                error;

    executor.set_windows_visible(false);

    source.chunk_map[1] = Capture::APIDumpLoader::DataChunk();

    ASSERT_TRUE(executor.execute(make_create_call(POPUP_STYLE,
                                                  64,
                                                  64),
                                 source,
                                &error) ) << error;
    ASSERT_TRUE(executor.execute(make_set_window_pos_call(DUMPED_HWND,
                                                          200,
                                                          120,
                                                          SWP_NOSIZE_FLAG,
                                                          true /* in_has_client */),
                                 source,
                                &error) ) << error;

    const SIZE client = get_client_size(&remapper);

    EXPECT_EQ(client.cx,
              64);
    EXPECT_EQ(client.cy,
              64);

    executor.shutdown();
}

TEST(Win32WindowResize, ACallOfADumpThatHasNoAreaForDrawingLeavesTheWindowAlone)
{
    Replay::ReplayEngineDLL::ObjectRemapper    remapper;
    Replay::ReplayEngineDLL::Win32CallExecutor executor(&remapper,
                                                        []() {},
                                                        [](const Replay::ReplayEngineDLL::WindowPlacement&) {});
    Tests::MapChunkSource                      source;
    std::string                                error;

    executor.set_windows_visible(false);

    source.chunk_map[1] = Capture::APIDumpLoader::DataChunk();

    ASSERT_TRUE(executor.execute(make_create_call(POPUP_STYLE,
                                                  64,
                                                  64),
                                 source,
                                &error) ) << error;
    ASSERT_TRUE(executor.execute(make_set_window_pos_call(DUMPED_HWND,
                                                          200,
                                                          120,
                                                          0, /* flags */
                                                          false /* in_has_client */),
                                 source,
                                &error) ) << error;

    const SIZE client = get_client_size(&remapper);

    EXPECT_EQ(client.cx,
              64);
    EXPECT_EQ(client.cy,
              64);

    executor.shutdown();
}

TEST(Win32WindowResize, AWindowTheReplayDoesNotHaveIsLeftAlone)
{
    constexpr uint64_t SYSTEM_HWND = 0x1234;

    Replay::ReplayEngineDLL::ObjectRemapper    remapper;
    Replay::ReplayEngineDLL::Win32CallExecutor executor(&remapper,
                                                        []() {},
                                                        [](const Replay::ReplayEngineDLL::WindowPlacement&) {});
    Tests::MapChunkSource                      source;
    std::string                                error;

    EXPECT_TRUE(executor.execute(make_set_window_pos_call(SYSTEM_HWND,
                                                          200,
                                                          120,
                                                          0, /* flags */
                                                          true /* in_has_client */),
                                 source,
                                &error) ) << error;
    EXPECT_TRUE(error.empty() );

    executor.shutdown();
}

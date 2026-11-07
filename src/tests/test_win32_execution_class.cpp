/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Tests for when the calls of the windowing API are made in a frame that is executed more than once: the swap of the buffers of a window waits for the
 * executions, so that what a frame drew is read before it.
 */
#include <gtest/gtest.h>
#include "object_remapper.h"
#include "win32_call_executor.h"

namespace
{
    Replay::ReplayEngineDLL::ExecutionClass get_class_of(const APIInterceptor::APIFunction& in_function)
    {
        Replay::ReplayEngineDLL::ObjectRemapper    remapper;
        Replay::ReplayEngineDLL::Win32CallExecutor executor(&remapper,
                                                            []() {},
                                                            [](const Replay::ReplayEngineDLL::WindowPlacement&) {});

        Capture::APIDumpLoader::DumpedAPICall call;

        call.func = in_function;

        return executor.get_execution_class(call);
    }
}

TEST(Win32CallExecutor, TheSwapOfTheBuffersOfAWindowComesAfterTheExecutionsOfAFrame)
{
    EXPECT_EQ(get_class_of(APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS),
              Replay::ReplayEngineDLL::ExecutionClass::AFTER_ALL);
}

TEST(Win32CallExecutor, TheOtherCallsAreMadeInTheFirstExecutionOnly)
{
    EXPECT_EQ(get_class_of(APIInterceptor::APIFUNCTION_WGL_WGLMAKECURRENT),
              Replay::ReplayEngineDLL::ExecutionClass::FIRST_TIME_ONLY);
    EXPECT_EQ(get_class_of(APIInterceptor::APIFUNCTION_GDI32_SETPIXELFORMAT),
              Replay::ReplayEngineDLL::ExecutionClass::FIRST_TIME_ONLY);
}

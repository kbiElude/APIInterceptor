/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Tests for FatalError: a value that no case handles ends the process, with the exit code and a message that says what it was.
 */
#include <gtest/gtest.h>
#include "common/macros.h"
#include <stdlib.h>

TEST(FatalError, AnUnsupportedValueEndsTheProcessAndSaysWhatItWas)
{
    const uint32_t unsupported_value = 77;

    /* The process has no console when the tests run from a tool, and would wait for somebody to close the box. */
    ::_putenv_s("APIINTERCEPTOR_NO_ERROR_DIALOG",
                "1");

    EXPECT_EXIT(AI_FAIL_UNSUPPORTED(unsupported_value),
                ::testing::ExitedWithCode(APIInterceptor::FatalError::get_exit_code() ),
                "Unsupported value 77 .*of .unsupported_value.");
}

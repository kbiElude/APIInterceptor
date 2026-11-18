/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Tests for FatalError: a value that no case handles ends the process, with the exit code and a message that says what it was.
 */
#include <gtest/gtest.h>
#include "common/macros.h"
#include <stdlib.h>

TEST(FatalError, AnAssertionThatDoesNotHoldEndsTheProcessAndSaysWhatIsNotImplemented)
{
    const bool is_supported = false;

    ::_putenv_s("APIINTERCEPTOR_NO_ERROR_DIALOG",
                "1");

    EXPECT_EXIT(AI_ASSERT_ALWAYS(is_supported,
                                 "The use is not implemented"),
                ::testing::ExitedWithCode(APIInterceptor::FatalError::get_exit_code() ),
                "Assertion .is_supported. does not hold");

    EXPECT_EXIT(AI_ASSERT_ALWAYS(is_supported,
                                 "The use is not implemented"),
                ::testing::ExitedWithCode(APIInterceptor::FatalError::get_exit_code() ),
                "The use is not implemented");
}

TEST(FatalError, AnAssertionThatHoldsDoesNothing)
{
    const bool is_supported = true;

    AI_ASSERT_ALWAYS(is_supported,
                     "Never said");

    SUCCEED();
}

TEST(FatalError, ForTestsAFailureThrowsAndSaysWhichKindItWasInsteadOfEndingTheProcess)
{
    const bool     is_supported      = false;
    const uint32_t unsupported_value = 5;

    APIInterceptor::FatalError::set_throws_for_tests(true);

    bool is_assertion_thrown   = false;
    bool is_unsupported_thrown = false;

    try
    {
        AI_ASSERT_ALWAYS(is_supported,
                         "The use is not implemented");
    }
    catch (const APIInterceptor::FatalError::Exception& in_exception)
    {
        is_assertion_thrown = (in_exception.is_unsupported_value() == false &&
                               std::string(in_exception.what() ).find("The use is not implemented") != std::string::npos);
    }

    try
    {
        AI_FAIL_UNSUPPORTED(unsupported_value);
    }
    catch (const APIInterceptor::FatalError::Exception& in_exception)
    {
        is_unsupported_thrown = (in_exception.is_unsupported_value() &&
                                 std::string(in_exception.what() ).find("unsupported_value") != std::string::npos);
    }

    APIInterceptor::FatalError::set_throws_for_tests(false);

    EXPECT_TRUE(is_assertion_thrown);
    EXPECT_TRUE(is_unsupported_thrown);
}

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

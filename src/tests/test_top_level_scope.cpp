/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of what counts as a top-level intercepted call: the calls a driver makes from within one do not, but those that the application
 * makes from a callback do.
 */
#include <gtest/gtest.h>
#include "common/top_level_scope.h"
#include "common/api_call_scope.h"

TEST(TopLevelScope, ACallWithinAnotherIsNotATopLevelOne)
{
    APIInterceptor::APICallScope outer;
    APIInterceptor::APICallScope inner;

    EXPECT_TRUE (outer.is_top_level_api_call() );
    EXPECT_FALSE(inner.is_top_level_api_call() );
}

TEST(TopLevelScope, ACallInTheScopeIsATopLevelOneAndTheNestingComesBackAfterIt)
{
    APIInterceptor::APICallScope outer;

    {
        APIInterceptor::TopLevelScope scope;
        APIInterceptor::APICallScope  in_callback;

        EXPECT_TRUE(in_callback.is_top_level_api_call() );
    }

    APIInterceptor::APICallScope after;

    EXPECT_TRUE (outer.is_top_level_api_call() );
    EXPECT_FALSE(after.is_top_level_api_call() );
}

/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

#include "Common/debug.h"
#include "Common/fatal_error.h"

#ifdef _DEBUG
    #define AI_ASSERT(assertion)                              \
        if ((assertion) == false)                             \
        {                                                     \
            APIInterceptor::Debug::assert_failed(__FILE__,    \
                                                 __LINE__,    \
                                                 #assertion); \
        }

    #define AI_ASSERT_FAIL()                                                  \
        APIInterceptor::Debug::assert_failed(__FILE__,                        \
                                             __LINE__,                        \
                                             "Unexpected condition detected");
#else
    #define AI_ASSERT(assertion)
    #define AI_ASSERT_FAIL()
#endif

/* For the default of a switch that is reached by a value which this code does not support (an enumerator that has no case): ends the
 * process, in every build, saying the value and where it is. Not for a default which has a meaning of its own.
 */
#define AI_FAIL_UNSUPPORTED(value)                \
    APIInterceptor::FatalError::unsupported_value(__FILE__,                   \
                                                  __LINE__,                   \
                                                  __FUNCTION__,               \
                                                  #value,                     \
                                                  static_cast<uint64_t>(value) )

#define AI_NOT_IMPLEMENTED() \
    MessageBox(HWND_DESKTOP, "Functionality not implemented!", __FUNCTION__ "()", MB_OK | MB_ICONERROR);

#endif /* COMMON_MACROS_H */
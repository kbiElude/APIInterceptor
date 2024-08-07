/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

#include "Common/debug.h"

#ifdef _DEBUG
    #define AI_ASSERT(assertion)                              \
        if (!(assertion))                                     \
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

#define AI_NOT_IMPLEMENTED() \
    MessageBox(HWND_DESKTOP, "Functionality not implemented!", __FUNCTION__ "()", MB_OK | MB_ICONERROR);

#endif /* COMMON_MACROS_H */
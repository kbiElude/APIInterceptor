/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_GLOBALS_H
#define COMMON_GLOBALS_H

#include "Common/logger.h"
#include "Common/types.h"

#define MAX_PER_FUNC_LOCAL_HELPER_STORAGE_SIZE (4096)

#if defined(_WIN32)
    #define AI_THREADLOCAL __declspec(thread)
#else
    #error todo
#endif

#endif /* COMMON_GLOBALS_H */
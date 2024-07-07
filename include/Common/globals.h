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

/* Two functions below must be implemented by APIInceptor library user projects. */
extern void on_api_interceptor_removed ();
extern void on_api_interceptor_injected();

#endif /* COMMON_GLOBALS_H */
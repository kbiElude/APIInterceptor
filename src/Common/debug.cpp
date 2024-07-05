/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if defined(_WIN32)
    #define _WIN32_WINNT 0x0501

    #include <Windows.h>
#endif

#include "Common/debug.h"
#include "Common/logger.h"

void APIInterceptor::Debug::assert_failed(const char*  in_filename,
                                          unsigned int in_line,
                                          const char*  in_message)
{
    AI_LOG(APIInterceptor::LogLevel::Error,
            "[!] Assertion failure in %s at %d: [%s]",
           in_filename,
           in_line,
           in_message);

    #if defined(_DEBUG)
    {
        #if defined(_WIN32)
        {
            if (::IsDebuggerPresent() )
            {
                _CrtDbgBreak();
            }
        }
        #else
        {
            #error TODO
        }
        #endif
    }
    #endif
}
/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_DEBUG_H
#define COMMON_DEBUG_H

namespace APIInterceptor
{
    namespace Debug
    {
        void assert_failed(const char*  in_filename,
                           unsigned int in_line,
                           const char*  in_message);
    }
}

#endif /* COMMON_DEBUG_H */
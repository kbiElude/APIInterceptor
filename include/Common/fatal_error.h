/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_FATAL_ERROR_H
#define COMMON_FATAL_ERROR_H

#include <stdint.h>

namespace APIInterceptor
{
    /* What ends the process when the code finds that it does not support something it was given (see AI_FAIL_UNSUPPORTED()): a
     * value of an enum that no case handles. It is a bug of this code, and what would follow is wrong output that is hard to trace,
     * so it is a failure in every build.
     */
    class FatalError
    {
    public:
        /* What the process exits with. */
        static uint32_t get_exit_code();

        /* Says what is not supported and where (to the standard error stream, to the debugger, and to the user in a box, unless the
         * process has a console or the environment has APIINTERCEPTOR_NO_ERROR_DIALOG), then ends the process.
         */
        [[noreturn]] static void unsupported_value(const char*     in_filename_ptr,
                                                   const uint32_t& in_line,
                                                   const char*     in_function_ptr,
                                                   const char*     in_expression_ptr,
                                                   const uint64_t& in_value);
    };
}

#endif /* COMMON_FATAL_ERROR_H */

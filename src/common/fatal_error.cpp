/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/fatal_error.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

uint32_t APIInterceptor::FatalError::get_exit_code()
{
    constexpr uint32_t EXIT_CODE = 0xA55E;

    return EXIT_CODE;
}

void APIInterceptor::FatalError::unsupported_value(const char*     in_filename_ptr,
                                                   const uint32_t& in_line,
                                                   const char*     in_function_ptr,
                                                   const char*     in_expression_ptr,
                                                   const uint64_t& in_value)
{
    constexpr size_t N_MESSAGE_CHARACTERS = 1024;

    char message_i8vec1024[N_MESSAGE_CHARACTERS] = {};

    ::snprintf(message_i8vec1024,
               sizeof(message_i8vec1024),
               "Unsupported value %llu (0x%llx) of \"%s\" in %s (%s:%u).\n"
               "The value is one that this code does not handle yet, and going on would give wrong results: the process is ended.",
               static_cast<unsigned long long>(in_value),
               static_cast<unsigned long long>(in_value),
               in_expression_ptr,
               in_function_ptr,
               in_filename_ptr,
               in_line);

    ::fprintf           (stderr,
                         "%s\n",
                         message_i8vec1024);
    ::fflush            (stderr);
    ::OutputDebugStringA(message_i8vec1024);

    /* A program that has no console (an application with a DLL injected into it) has nowhere else to say it. */
    const auto console_window = ::GetConsoleWindow();

    if (console_window == nullptr)
    {
        const auto n_variable_chars = ::GetEnvironmentVariableA("APIINTERCEPTOR_NO_ERROR_DIALOG",
                                                                nullptr,
                                                                0);

        if (n_variable_chars == 0)
        {
            ::MessageBoxA(nullptr,
                          message_i8vec1024,
                          "API Interceptor: unsupported value",
                          MB_OK | MB_ICONERROR | MB_TOPMOST | MB_SETFOREGROUND);
        }
    }

    ::TerminateProcess(::GetCurrentProcess(),
                       get_exit_code() );

    /* TerminateProcess does not return for the calling process; this keeps the compiler and the reader sure of it. */
    ::abort();
}

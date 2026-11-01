/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What the tests of the interceptor, and of a project that builds on it, name and look for.
 */
#ifndef TESTS_FIXTURES_H
#define TESTS_FIXTURES_H

#include <string>

namespace Tests
{
    class Fixtures
    {
    public:
        /* The path of the program which runs the tests: a file which is there, and is not what a test asks a loader for. */
        static std::string get_test_executable_path();

        /* A file which is there and is not an executable (data/README.txt). */
        static std::string get_text_file_path();
    };
}

#endif /* TESTS_FIXTURES_H */

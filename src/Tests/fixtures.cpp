/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "fixtures.h"
#include <Windows.h>

std::string Tests::Fixtures::get_test_executable_path()
{
    char path_i8vec260[MAX_PATH] = {};

    ::GetModuleFileNameA(nullptr,
                         path_i8vec260,
                         MAX_PATH);

    return path_i8vec260;
}

std::string Tests::Fixtures::get_text_file_path()
{
    return std::string(APIINTERCEPTOR_TESTS_DATA_DIR) + "/README.txt";
}

/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/hooks/WGL/utils.h"

uint32_t Interception::Hooks::WGL::Utils::get_n_context_attrib_list_ints(const int* in_attrib_list_ptr)
{
    /* A list which does not end is a sign of a bad pointer; none of the real ones comes anywhere near this. */
    constexpr uint32_t MAX_N_PAIRS = 1024;

    uint32_t n_pairs = 0;
    uint32_t result  = 0;

    if (in_attrib_list_ptr == nullptr)
    {
        goto end;
    }

    while (in_attrib_list_ptr[2 * n_pairs] != 0 &&
           n_pairs                         <  MAX_N_PAIRS)
    {
        n_pairs++;
    }

    /* The terminator is included. */
    result = 2 * n_pairs + 1;
end:
    return result;
}

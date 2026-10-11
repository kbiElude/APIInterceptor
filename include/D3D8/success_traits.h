/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Tells if a returned value reports success. Only HRESULTs do.
 */
#ifndef D3D8_SUCCESS_TRAITS_H
#define D3D8_SUCCESS_TRAITS_H

#include "D3D8/types.h"

namespace D3D8
{
    template<typename T>
    struct SuccessTraits
    {
        static bool is_success(const T& in_value);
    };

    template<>
    struct SuccessTraits<long>
    {
        static bool is_success(const long& in_value);
    };
}

template<typename T>
bool D3D8::SuccessTraits<T>::is_success(const T& in_value)
{
    (void) in_value;

    return false;
}

#endif /* D3D8_SUCCESS_TRAITS_H */

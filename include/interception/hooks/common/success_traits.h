/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Tells if a returned value reports success. Only HRESULTs do.
 */
#ifndef HOOKS_COMMON_SUCCESS_TRAITS_H
#define HOOKS_COMMON_SUCCESS_TRAITS_H

#include "interception/hooks/common/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace Common
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
    }
}

template<typename T>
bool Interception::Hooks::Common::SuccessTraits<T>::is_success(const T& in_value)
{
    (void) in_value;

    return false;
}

#endif /* HOOKS_COMMON_SUCCESS_TRAITS_H */

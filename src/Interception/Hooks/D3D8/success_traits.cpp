/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Hooks/D3D8/success_traits.h"

bool Interception::Hooks::D3D8::SuccessTraits<long>::is_success(const long& in_value)
{
    return SUCCEEDED(in_value);
}

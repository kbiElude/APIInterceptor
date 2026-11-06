/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/hooks/common/hook_result.h"

void Interception::Hooks::Common::HookResult<void>::get() const
{
    /* Stub */
}

bool Interception::Hooks::Common::HookResult<void>::is_success() const
{
    return false;
}

/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Hooks/D3D8/argument_factory.h"
#include "Interception/Hooks/D3D8/hook_result.h"

APIInterceptor::APIFunctionArgument Interception::Hooks::D3D8::HookResult<void>::create_argument() const
{
    return ArgumentFactory::create_unknown();
}

void Interception::Hooks::D3D8::HookResult<void>::get() const
{
    /* Stub */
}

bool Interception::Hooks::D3D8::HookResult<void>::is_success() const
{
    return false;
}

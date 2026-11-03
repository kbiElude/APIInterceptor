/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Hooks the interface returned through an interface pointer argument.
 */
#ifndef D3D7_OBJECT_PATCHER_H
#define D3D7_OBJECT_PATCHER_H

#include "Interception/Core/D3D7Utils/types.h"
#include "Interception/Hooks/D3D7/hook_table.h"

namespace Interception
{
    namespace Hooks
    {
        namespace D3D7
        {
            template<typename T,
                     bool     is_object_out = (Interception::Core::D3D7Utils::ArgumentCategoryOf<T>::value == Interception::Hooks::Common::ArgumentCategory::OBJECT_OUT)>
            struct ObjectPatcher
            {
                static void patch(const T& in_value);
            };

            template<typename T>
            struct ObjectPatcher<T, true>
            {
                typedef typename std::remove_pointer<typename std::remove_pointer<T>::type>::type InterfaceType;

                static void patch(const T& in_value);
            };
        }
    }
}

template<typename T,
         bool     is_object_out>
void Interception::Hooks::D3D7::ObjectPatcher<T, is_object_out>::patch(const T& in_value)
{
    (void) in_value;
}

template<typename T>
void Interception::Hooks::D3D7::ObjectPatcher<T, true>::patch(const T& in_value)
{
    if (in_value  != nullptr &&
       *in_value  != nullptr)
    {
        const Interface interface_value = Interception::Core::D3D7Utils::InterfaceTraits<InterfaceType>::interface_value;

        get_hook_table_ptr()->patch_object(static_cast<uint32_t>(interface_value),
                                           *in_value);
    }
}

#endif /* D3D7_OBJECT_PATCHER_H */

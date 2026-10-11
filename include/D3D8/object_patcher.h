/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Hooks the interface returned through an interface pointer argument.
 */
#ifndef D3D8_OBJECT_PATCHER_H
#define D3D8_OBJECT_PATCHER_H

#include "D3D8/hook_table.h"
#include "D3D8Utils/types.h"

namespace D3D8
{
    template<typename T,
             bool     is_object_out = (Utils::ArgumentCategoryOf<T>::value == Utils::ArgumentCategory::ObjectOut)>
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

template<typename T,
         bool     is_object_out>
void D3D8::ObjectPatcher<T, is_object_out>::patch(const T& in_value)
{
    (void) in_value;
}

template<typename T>
void D3D8::ObjectPatcher<T, true>::patch(const T& in_value)
{
    if (in_value  != nullptr &&
       *in_value  != nullptr)
    {
        const Interface interface_value = Utils::InterfaceTraits<InterfaceType>::interface_value;

        HookTable::get_ptr()->patch_object(interface_value,
                                          *in_value);
    }
}

#endif /* D3D8_OBJECT_PATCHER_H */

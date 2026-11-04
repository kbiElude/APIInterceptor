/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Hooks/Common/generic_hook.h"
#include "Interception/Hooks/D3D8/hook_table.h"
#include "Interception/Hooks/D3D8/hook_traits.h"

Interception::Hooks::Common::HookTable* Interception::Hooks::D3D8::get_hook_table_ptr()
{
    /* Thread-safe initialization: the table is not changed afterwards. */
    static Interception::Hooks::Common::HookTable* result_ptr = []()
    {
        auto hook_table_ptr = new Interception::Hooks::Common::HookTable();

        #define D3D8_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters) \
            hook_table_ptr->add_hook_entry(static_cast<uint32_t>(Interface::INTERFACE_TAG), \
                                           Interception::Hooks::Common::make_vtable_hook_entry<HookTraits, \
                                                                                               PFN_##INTERFACE_TAG##_##METHOD_TAG, \
                                                                                               APIInterceptor::APIFUNCTION_D3D8_##INTERFACE_TAG##_##METHOD_TAG, \
                                                                                               VTABLE_INDEX_##INTERFACE_TAG##_##METHOD_TAG>() );
        #include "Interception/Hooks/D3D8/d3d8_methods.inl"
        #undef D3D8_METHOD

        return hook_table_ptr;
    }();

    return result_ptr;
}

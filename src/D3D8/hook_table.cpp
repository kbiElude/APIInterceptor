/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "D3D8/generic_hook.h"
#include "D3D8/hook_table.h"
#include "D3D8/vtable_registry.h"

D3D8::HookTable::HookTable()
{
    m_hook_entry_vec_vec.resize(static_cast<uint32_t>(Interface::Count) );

    #define D3D8_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters) \
        m_hook_entry_vec_vec.at(static_cast<uint32_t>(Interface::INTERFACE_TAG) ).push_back( \
            {reinterpret_cast<void*>(&GenericHook<PFN_##INTERFACE_TAG##_##METHOD_TAG, \
                                                  APIInterceptor::APIFUNCTION_D3D8_##INTERFACE_TAG##_##METHOD_TAG, \
                                                  VTABLE_INDEX_##INTERFACE_TAG##_##METHOD_TAG>::invoke), \
             VTABLE_INDEX_##INTERFACE_TAG##_##METHOD_TAG} \
        );
    #include "D3D8/d3d8_methods.inl"
    #undef D3D8_METHOD
}

D3D8::HookTable* D3D8::HookTable::get_ptr()
{
    static HookTable instance;

    return &instance;
}

void D3D8::HookTable::get_hook_entries(const Interface& in_interface,
                                       const HookEntry** out_hook_entry_array_ptr_ptr,
                                       uint32_t*         out_n_hook_entries_ptr) const
{
    const auto n_interface = static_cast<uint32_t>(in_interface);

    *out_hook_entry_array_ptr_ptr = nullptr;
    *out_n_hook_entries_ptr       = 0;

    if (n_interface < m_hook_entry_vec_vec.size() )
    {
        const auto& hook_entry_vec = m_hook_entry_vec_vec.at(n_interface);

        *out_hook_entry_array_ptr_ptr = hook_entry_vec.data();
        *out_n_hook_entries_ptr       = static_cast<uint32_t>(hook_entry_vec.size() );
    }
}

void D3D8::HookTable::patch_object(const Interface& in_interface,
                                   const void*      in_object_ptr)
{
    const HookEntry* hook_entry_array_ptr = nullptr;
    uint32_t         n_hook_entries       = 0;

    get_hook_entries(in_interface,
                    &hook_entry_array_ptr,
                    &n_hook_entries);

    if (in_object_ptr        != nullptr &&
        hook_entry_array_ptr != nullptr)
    {
        VTableRegistry::get_ptr()->patch_vtable(in_interface,
                                                in_object_ptr,
                                                hook_entry_array_ptr,
                                                n_hook_entries);
    }
}

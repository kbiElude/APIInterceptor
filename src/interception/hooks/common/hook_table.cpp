/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/hooks/common/hook_table.h"
#include "interception/hooks/common/vtable_registry.h"

void Interception::Hooks::Common::HookTable::add_hook_entry(const uint32_t&  in_interface_id,
                                                            const HookEntry& in_hook_entry)
{
    if (in_interface_id >= m_hook_entry_vec_vec.size() )
    {
        m_hook_entry_vec_vec.resize(in_interface_id + 1);
    }

    m_hook_entry_vec_vec.at(in_interface_id).push_back(in_hook_entry);
}

void Interception::Hooks::Common::HookTable::get_hook_entries(const uint32_t&   in_interface_id,
                                                              const HookEntry** out_hook_entry_array_ptr_ptr,
                                                              uint32_t*         out_n_hook_entries_ptr) const
{
    *out_hook_entry_array_ptr_ptr = nullptr;
    *out_n_hook_entries_ptr       = 0;

    if (in_interface_id < m_hook_entry_vec_vec.size() )
    {
        const auto& hook_entry_vec = m_hook_entry_vec_vec.at(in_interface_id);

        *out_hook_entry_array_ptr_ptr = hook_entry_vec.data();
        *out_n_hook_entries_ptr       = static_cast<uint32_t>(hook_entry_vec.size() );
    }
}

void Interception::Hooks::Common::HookTable::patch_object(const uint32_t& in_interface_id,
                                                          const void*     in_object_ptr)
{
    const HookEntry* hook_entry_array_ptr = nullptr;
    uint32_t         n_hook_entries       = 0;

    get_hook_entries(in_interface_id,
                    &hook_entry_array_ptr,
                    &n_hook_entries);

    if (in_object_ptr        != nullptr &&
        hook_entry_array_ptr != nullptr)
    {
        /* The methods of an interface are numbered from 0 without gaps, so the highest slot gives the vtable's size. */
        uint32_t n_methods = 0;

        for (uint32_t n_hook_entry = 0;
                      n_hook_entry < n_hook_entries;
                    ++n_hook_entry)
        {
            const uint32_t n_methods_through_entry = hook_entry_array_ptr[n_hook_entry].vtable_index + 1;

            if (n_methods_through_entry > n_methods)
            {
                n_methods = n_methods_through_entry;
            }
        }

        VTableRegistry::get_ptr()->patch_vtable(in_interface_id,
                                                n_methods,
                                                in_object_ptr,
                                                hook_entry_array_ptr,
                                                n_hook_entries);
    }
}

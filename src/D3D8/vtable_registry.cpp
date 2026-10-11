/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "D3D8/vtable_registry.h"
#include "D3D8Utils/methods.h"
#include <Windows.h>

D3D8::VTableRegistry* D3D8::VTableRegistry::get_ptr()
{
    /* Never destroyed: hooks can still run during shutdown. */
    static VTableRegistry* instance_ptr = new VTableRegistry();

    return instance_ptr;
}

void* D3D8::VTableRegistry::get_original_function_ptr(const void*     in_object_ptr,
                                                      const uint32_t& in_vtable_index)
{
    void* result_ptr = nullptr;

    if (in_object_ptr != nullptr)
    {
        void** vtable_ptr = *reinterpret_cast<void** const*>(in_object_ptr);

        {
            std::lock_guard<std::mutex> lock    (m_mutex);
            const auto                  iterator = m_patched_vtable_map.find(vtable_ptr);

            if (iterator        != m_patched_vtable_map.end()                         &&
                in_vtable_index <  iterator->second.original_function_ptr_vec.size() )
            {
                result_ptr = iterator->second.original_function_ptr_vec.at(in_vtable_index);
            }
        }
    }

    return result_ptr;
}

bool D3D8::VTableRegistry::patch_vtable(const Interface& in_interface,
                                        const void*      in_object_ptr,
                                        const HookEntry* in_hook_entry_array_ptr,
                                        uint32_t         in_n_hook_entries)
{
    bool result = false;

    if (in_object_ptr != nullptr)
    {
        void** vtable_ptr = *reinterpret_cast<void** const*>(in_object_ptr);

        {
            std::lock_guard<std::mutex> lock    (m_mutex);
            auto                        iterator = m_patched_vtable_map.find(vtable_ptr);

            if (iterator == m_patched_vtable_map.end() )
            {
                PatchedVtable new_vtable;

                new_vtable.interface_type = in_interface;

                new_vtable.original_function_ptr_vec.resize(Utils::get_n_methods(in_interface) );
                iterator = m_patched_vtable_map.emplace(vtable_ptr,
                                                        std::move(new_vtable) ).first;
            }

            AI_ASSERT(iterator->second.interface_type == in_interface);

            for (uint32_t n_hook_entry = 0;
                          n_hook_entry < in_n_hook_entries;
                        ++n_hook_entry)
            {
                const auto& hook_entry  = in_hook_entry_array_ptr[n_hook_entry];
                DWORD       old_protect = 0;

                if (hook_entry.vtable_index >= iterator->second.original_function_ptr_vec.size() )
                {
                    AI_ASSERT_FAIL();

                    continue;
                }

                /* Judge by the slot's contents: a new object can reuse a destroyed vtable's address. */
                if (vtable_ptr[hook_entry.vtable_index] == hook_entry.hook_function_ptr)
                {
                    /* Already hooked. */
                    continue;
                }

                if (::VirtualProtect(vtable_ptr + hook_entry.vtable_index,
                                     sizeof(void*),
                                     PAGE_READWRITE,
                                    &old_protect) == FALSE)
                {
                    AI_ASSERT_FAIL();

                    continue;
                }

                iterator->second.original_function_ptr_vec.at(hook_entry.vtable_index) = vtable_ptr[hook_entry.vtable_index];
                vtable_ptr[hook_entry.vtable_index]                                   = hook_entry.hook_function_ptr;

                ::VirtualProtect(vtable_ptr + hook_entry.vtable_index,
                                 sizeof(void*),
                                 old_protect,
                                &old_protect);
            }
        }

        result = true;
    }

    return result;
}

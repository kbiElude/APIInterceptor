/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "Interception/Hooks/Common/vtable_registry.h"
#include <Windows.h>

void* Interception::Hooks::Common::VTableRegistry::get_original_function_ptr(const void*     in_object_ptr,
                                                                             const uint32_t& in_vtable_index)
{
    constexpr size_t N_CACHE_ENTRIES = 64; /* a power of two */

    /* A hook runs for every call of the application, from the thread of the call: the vtable is found without the lock, in a cache
     * which the thread has to itself. The entries of the map are never erased, and their vectors never change size, so a pointer to a
     * vector stays valid.
     */
    struct CacheEntry
    {
        const std::vector<void*>* original_function_ptr_vec_ptr;
        void**                    vtable_ptr;
    };

    static thread_local CacheEntry cache_entry_vec[N_CACHE_ENTRIES] = {};

    void* result_ptr = nullptr;

    if (in_object_ptr != nullptr)
    {
        void**      vtable_ptr  = *reinterpret_cast<void** const*>(in_object_ptr);
        CacheEntry& cache_entry = cache_entry_vec[(reinterpret_cast<uintptr_t>(vtable_ptr) >> 4) & (N_CACHE_ENTRIES - 1)];

        if (cache_entry.vtable_ptr != vtable_ptr)
        {
            std::lock_guard<std::mutex> lock    (m_mutex);
            const auto                  iterator = m_patched_vtable_map.find(vtable_ptr);

            if (iterator != m_patched_vtable_map.end() )
            {
                cache_entry.original_function_ptr_vec_ptr = &iterator->second.original_function_ptr_vec;
                cache_entry.vtable_ptr                    = vtable_ptr;
            }
        }

        if (cache_entry.vtable_ptr == vtable_ptr                                         &&
            in_vtable_index        <  cache_entry.original_function_ptr_vec_ptr->size() )
        {
            result_ptr = cache_entry.original_function_ptr_vec_ptr->at(in_vtable_index);
        }
    }

    return result_ptr;
}

Interception::Hooks::Common::VTableRegistry* Interception::Hooks::Common::VTableRegistry::get_ptr()
{
    /* Never destroyed: hooks can still run during shutdown. */
    static VTableRegistry* instance_ptr = new VTableRegistry();

    return instance_ptr;
}

bool Interception::Hooks::Common::VTableRegistry::patch_vtable(const uint32_t&  in_interface_id,
                                                               const uint32_t&  in_n_methods,
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

                new_vtable.interface_id = in_interface_id;

                new_vtable.original_function_ptr_vec.resize(in_n_methods);
                iterator = m_patched_vtable_map.emplace(vtable_ptr,
                                                        std::move(new_vtable) ).first;
            }

            AI_ASSERT(iterator->second.interface_id == in_interface_id);

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

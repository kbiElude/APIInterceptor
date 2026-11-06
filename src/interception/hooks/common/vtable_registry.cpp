/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/macros.h"
#include "interception/hooks/common/vtable_registry.h"
#include <Windows.h>

void* Interception::Hooks::Common::VTableRegistry::get_original_function_ptr(const void*     in_object_ptr,
                                                                             const uint32_t& in_vtable_index)
{
    void* result_ptr = nullptr;

    if (in_object_ptr != nullptr)
    {
        const PatchedVtable* patched_vtable_ptr = get_patched_vtable_ptr(*reinterpret_cast<void** const*>(in_object_ptr) );

        if (patched_vtable_ptr != nullptr                                                &&
            in_vtable_index    <  patched_vtable_ptr->original_function_ptr_vec.size() )
        {
            result_ptr = patched_vtable_ptr->original_function_ptr_vec.at(in_vtable_index);
        }
    }

    return result_ptr;
}

Interception::Hooks::Common::VTableRegistry::PatchedVtable* Interception::Hooks::Common::VTableRegistry::get_patched_vtable_ptr(void** in_vtable_ptr)
{
    constexpr size_t N_CACHE_ENTRIES = 64; /* a power of two */

    struct CacheEntry
    {
        PatchedVtable* patched_vtable_ptr;
        void**         vtable_ptr;
    };

    static thread_local CacheEntry cache_entry_vec[N_CACHE_ENTRIES] = {};

    CacheEntry& cache_entry = cache_entry_vec[(reinterpret_cast<uintptr_t>(in_vtable_ptr) >> 4) & (N_CACHE_ENTRIES - 1)];

    if (cache_entry.vtable_ptr != in_vtable_ptr)
    {
        std::lock_guard<std::mutex> lock    (m_mutex);
        const auto                  iterator = m_patched_vtable_map.find(in_vtable_ptr);

        if (iterator != m_patched_vtable_map.end() )
        {
            cache_entry.patched_vtable_ptr = &iterator->second;
            cache_entry.vtable_ptr         = in_vtable_ptr;
        }
    }

    return (cache_entry.vtable_ptr == in_vtable_ptr) ? cache_entry.patched_vtable_ptr
                                                     : nullptr;
}

Interception::Hooks::Common::VTableRegistry* Interception::Hooks::Common::VTableRegistry::get_ptr()
{
    /* Never destroyed: hooks can still run during shutdown. */
    static VTableRegistry* instance_ptr = new VTableRegistry();

    return instance_ptr;
}

void Interception::Hooks::Common::VTableRegistry::hook_slot(void**          in_vtable_ptr,
                                                            PatchedVtable*  inout_patched_vtable_ptr,
                                                            const uint32_t& in_vtable_index,
                                                            void*           in_hook_function_ptr)
{
    DWORD old_protect = 0;

    inout_patched_vtable_ptr->hook_function_ptr_vec.at(in_vtable_index) = in_hook_function_ptr;

    if (::VirtualProtect(in_vtable_ptr + in_vtable_index,
                         sizeof(void*),
                         PAGE_READWRITE,
                        &old_protect) == FALSE)
    {
        AI_ASSERT_FAIL();
    }
    else
    {
        inout_patched_vtable_ptr->original_function_ptr_vec.at(in_vtable_index) = in_vtable_ptr[in_vtable_index];
        in_vtable_ptr[in_vtable_index]                                         = in_hook_function_ptr;

        ::VirtualProtect(in_vtable_ptr + in_vtable_index,
                         sizeof(void*),
                         old_protect,
                        &old_protect);
    }
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

                new_vtable.hook_function_ptr_vec.resize    (in_n_methods);
                new_vtable.original_function_ptr_vec.resize(in_n_methods);
                iterator = m_patched_vtable_map.emplace(vtable_ptr,
                                                        std::move(new_vtable) ).first;
            }

            AI_ASSERT(iterator->second.interface_id == in_interface_id);

            for (uint32_t n_hook_entry = 0;
                          n_hook_entry < in_n_hook_entries;
                        ++n_hook_entry)
            {
                const auto& hook_entry = in_hook_entry_array_ptr[n_hook_entry];

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

                hook_slot(vtable_ptr,
                         &iterator->second,
                          hook_entry.vtable_index,
                          hook_entry.hook_function_ptr);
            }
        }

        result = true;
    }

    return result;
}

void Interception::Hooks::Common::VTableRegistry::repair_vtable(const void* in_object_ptr)
{
    if (in_object_ptr != nullptr)
    {
        void**         vtable_ptr         = *reinterpret_cast<void** const*>(in_object_ptr);
        PatchedVtable* patched_vtable_ptr = get_patched_vtable_ptr(vtable_ptr);

        if (patched_vtable_ptr != nullptr)
        {
            for (uint32_t n_slot = 0;
                          n_slot < static_cast<uint32_t>(patched_vtable_ptr->hook_function_ptr_vec.size() );
                        ++n_slot)
            {
                void* const hook_function_ptr = patched_vtable_ptr->hook_function_ptr_vec.at(n_slot);

                if (hook_function_ptr != nullptr                &&
                    vtable_ptr[n_slot] != hook_function_ptr)
                {
                    std::lock_guard<std::mutex> lock(m_mutex);

                    if (vtable_ptr[n_slot] != hook_function_ptr)
                    {
                        hook_slot(vtable_ptr,
                                  patched_vtable_ptr,
                                  n_slot,
                                  hook_function_ptr);
                    }
                }
            }
        }
    }
}

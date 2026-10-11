/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Patches COM vtables in place, keeping COM pointer identity. Originals are kept per vtable address, since one
 * interface can be implemented by several classes. Vtables are never restored: they can be heap-allocated and freed.
 */
#ifndef D3D8_VTABLE_REGISTRY_H
#define D3D8_VTABLE_REGISTRY_H

#include "D3D8/types.h"
#include <mutex>
#include <unordered_map>
#include <vector>

namespace D3D8
{
    class VTableRegistry
    {
    public:
        static VTableRegistry* get_ptr();

        /* Returns nullptr if the slot has not been hooked. */
        void* get_original_function_ptr(const void*     in_object_ptr,
                                        const uint32_t& in_vtable_index);

        /* Hooks the slots in the object's vtable, skipping those already hooked. Returns false for a null object. */
        bool patch_vtable(const Interface& in_interface,
                          const void*      in_object_ptr,
                          const HookEntry* in_hook_entry_array_ptr,
                          uint32_t         in_n_hook_entries);

    private:
        struct PatchedVtable
        {
            Interface          interface_type;
            std::vector<void*> original_function_ptr_vec; /* indexed by vtable slot; nullptr = not hooked */
        };

        std::mutex                                m_mutex;
        std::unordered_map<void**, PatchedVtable> m_patched_vtable_map;
    };
}

#endif /* D3D8_VTABLE_REGISTRY_H */

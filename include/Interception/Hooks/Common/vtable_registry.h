/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Patches COM vtables in place, keeping COM pointer identity. Originals are kept per vtable address, since one
 * interface can be implemented by several classes. Vtables are never restored: they can be heap-allocated and freed.
 */
#ifndef HOOKS_COMMON_VTABLE_REGISTRY_H
#define HOOKS_COMMON_VTABLE_REGISTRY_H

#include "Interception/Hooks/Common/types.h"
#include <mutex>
#include <unordered_map>
#include <vector>

namespace Interception
{
    namespace Hooks
    {
        namespace Common
        {
            class VTableRegistry
            {
            public:
                /* Returns nullptr if the slot has not been hooked. */
                void* get_original_function_ptr(const void*     in_object_ptr,
                                                const uint32_t& in_vtable_index);

                /* Hooks the slots in the object's vtable, skipping those already hooked. Returns false for a null object. */
                bool patch_vtable(const uint32_t&  in_interface_id,
                                  const uint32_t&  in_n_methods,
                                  const void*      in_object_ptr,
                                  const HookEntry* in_hook_entry_array_ptr,
                                  uint32_t         in_n_hook_entries);

                static VTableRegistry* get_ptr();

            private:
                struct PatchedVtable
                {
                    uint32_t           interface_id; /* the API's own id */
                    std::vector<void*> original_function_ptr_vec; /* indexed by vtable slot; nullptr = not hooked */
                };

                std::mutex                                m_mutex;
                std::unordered_map<void**, PatchedVtable> m_patched_vtable_map;
            };
        }
    }
}

#endif /* HOOKS_COMMON_VTABLE_REGISTRY_H */

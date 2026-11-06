/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The hooks of the methods of the interfaces of one API. The API fills it in once, from its method table, with its own
 * interface ids; the hooks are put into the vtables of the objects the application gets.
 */
#ifndef HOOKS_COMMON_HOOK_TABLE_H
#define HOOKS_COMMON_HOOK_TABLE_H

#include "interception/hooks/common/types.h"
#include <vector>

namespace Interception
{
    namespace Hooks
    {
        namespace Common
        {
            class HookTable
            {
            public:
                /* Not safe to call while the application runs; the table is filled before any object is hooked. */
                void add_hook_entry(const uint32_t&  in_interface_id,
                                    const HookEntry& in_hook_entry);

                /* The entries are valid for the lifetime of the table. Empty for interfaces which are not in the table. */
                void get_hook_entries(const uint32_t&   in_interface_id,
                                      const HookEntry** out_hook_entry_array_ptr_ptr,
                                      uint32_t*         out_n_hook_entries_ptr) const;

                /* Hooks all methods of the object's interface. Does nothing for a null object or an unknown interface. */
                void patch_object(const uint32_t& in_interface_id,
                                  const void*     in_object_ptr);

            private:
                std::vector<std::vector<HookEntry> > m_hook_entry_vec_vec; /* indexed by interface id */
            };
        }
    }
}

#endif /* HOOKS_COMMON_HOOK_TABLE_H */

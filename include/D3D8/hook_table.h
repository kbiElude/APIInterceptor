/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Hooks of all methods of every interface of the D3D8 method table.
 */
#ifndef D3D8_HOOK_TABLE_H
#define D3D8_HOOK_TABLE_H

#include "D3D8/types.h"
#include <vector>

namespace D3D8
{
    class HookTable
    {
    public:
        static HookTable* get_ptr();

        /* The entries are valid for the lifetime of the process. Empty for interfaces which are not in the table. */
        void get_hook_entries(const Interface&  in_interface,
                              const HookEntry** out_hook_entry_array_ptr_ptr,
                              uint32_t*         out_n_hook_entries_ptr) const;

        /* Hooks all methods of the object's interface. Does nothing for a null object or an unknown interface. */
        void patch_object(const Interface& in_interface,
                          const void*      in_object_ptr);

    private:
        HookTable();

        std::vector<std::vector<HookEntry> > m_hook_entry_vec_vec; /* indexed by interface */
    };
}

#endif /* D3D8_HOOK_TABLE_H */

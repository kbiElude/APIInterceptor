/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The hooks of all methods of every interface of the D3D7 method table.
 */
#ifndef D3D7_HOOK_TABLE_H
#define D3D7_HOOK_TABLE_H

#include "Interception/Hooks/Common/hook_table.h"

namespace Interception
{
    namespace Hooks
    {
        namespace D3D7
        {
            /* Filled in on the first call, from the D3D7 method table. Indexed by Interface. */
            Interception::Hooks::Common::HookTable* get_hook_table_ptr();
        }
    }
}

#endif /* D3D7_HOOK_TABLE_H */

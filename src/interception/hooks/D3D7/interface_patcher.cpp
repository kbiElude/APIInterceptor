/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/hooks/D3D7/hook_table.h"
#include "interception/hooks/D3D7/interface_patcher.h"
#include "interception/core/D3D7Utils/guids.h"

void Interception::Hooks::D3D7::InterfacePatcher::patch_object_for_iid(const GUID& in_iid,
                                                                       void*       in_object_ptr)
{
    const auto* known_guid_ptr = Interception::Core::D3D7Utils::find_known_guid(in_iid);

    if (in_object_ptr   != nullptr &&
        known_guid_ptr  != nullptr &&
        known_guid_ptr->interface_type != Interface::UNKNOWN)
    {
        get_hook_table_ptr()->patch_object(static_cast<uint32_t>(known_guid_ptr->interface_type),
                                           in_object_ptr);
    }
}

/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Hooks/D3D7/hook_policy.h"
#include "Interception/Hooks/D3D7/hook_table.h"

void Interception::Hooks::D3D7::HookPolicy<APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW7_QUERYINTERFACE>::on_call_finished(const bool& in_is_success,
                                                                                                                           IDirectDraw7* in_self,
                                                                                                                           const GUID&   in_iid,
                                                                                                                           void**        in_object_ptr_ptr)
{
    /* IID_IDirect3D7 */
    static const GUID IID_DIRECT3D7 = {0xf5049e77, 0x4861, 0x11d2, {0xa4, 0x07, 0x00, 0xa0, 0xc9, 0x06, 0x29, 0xa8} };

    (void) in_self;

    if (in_is_success                 &&
        in_object_ptr_ptr != nullptr  &&
       *in_object_ptr_ptr != nullptr)
    {
        if (::IsEqualGUID(in_iid,
                          IID_DIRECT3D7) )
        {
            get_hook_table_ptr()->patch_object(static_cast<uint32_t>(Interface::IDIRECT3D7),
                                              *in_object_ptr_ptr);
        }
    }
}

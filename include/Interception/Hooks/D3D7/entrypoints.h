/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Hook of the D3D7 function exported by ddraw.dll. Methods are hooked by D3D7/hook_table.h.
 */
#ifndef D3D7_ENTRYPOINTS_H
#define D3D7_ENTRYPOINTS_H

#include "Interception/Hooks/D3D7/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace D3D7
        {
            HRESULT __stdcall aiDirectDrawCreateEx(GUID*        in_guid_ptr,
                                                   void**       out_direct_draw_ptr_ptr,
                                                   const GUID&  in_iid,
                                                   IUnknown*    in_outer_ptr);
        }
    }
}

#endif /* D3D7_ENTRYPOINTS_H */

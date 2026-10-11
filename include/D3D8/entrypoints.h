/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Hook of the D3D8 function exported by d3d8.dll. Methods are hooked by D3D8/hook_table.h.
 */
#ifndef D3D8_ENTRYPOINTS_H
#define D3D8_ENTRYPOINTS_H

#include "D3D8/types.h"

namespace D3D8
{
    IDirect3D8* __stdcall aiDirect3DCreate8(UINT in_sdk_version);
}

#endif /* D3D8_ENTRYPOINTS_H */

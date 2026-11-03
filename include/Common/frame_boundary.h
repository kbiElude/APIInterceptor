/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_FRAME_BOUNDARY_H
#define COMMON_FRAME_BOUNDARY_H

#include "Common/types.h"

namespace APIInterceptor
{
    /* Tells if a call of the function ends a frame: what the hooks, the dumper, the printer and the replay all agree on.
     * IDirect3DSwapChain8::Present is not one, as it presents additional swap chains. Of Direct3D 7, only the flip of surfaces
     * is: the copy of a frame into a window (a Blt to the primary surface) is not recognized yet.
     */
    constexpr bool is_frame_boundary(const APIFunction& in_function)
    {
        return in_function == APIFUNCTION_GDI32_SWAPBUFFERS             ||
               in_function == APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_FLIP ||
               in_function == APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT;
    }
}

#endif /* COMMON_FRAME_BOUNDARY_H */

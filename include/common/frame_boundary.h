/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_FRAME_BOUNDARY_H
#define COMMON_FRAME_BOUNDARY_H

#include "common/api_function_argument.h"
#include "common/types.h"

namespace APIInterceptor
{
    /* The argument that the hooks of IDirectDrawSurface7::Blt and ::BltFast add (after the 6 of the method), which is not 0 if the
     * surface that is blitted to is the primary one: the copy of a frame to the screen, which is how a program ends a frame when it
     * does not flip. Both methods have it in the same place.
     */
    constexpr uint32_t D3D7_BLT_PRESENTS_ARGUMENT = 6;

    /* Tells if a call of the function ends a frame: what the hooks, the dumper, the printer and the replay all agree on. The
     * arguments are those of the call, the extra ones which the hooks add included. A function whose calls do not all end a frame
     * is told by them: a blit does if it is made to the primary surface. IDirect3DSwapChain8::Present is not a boundary, as it
     * presents additional swap chains.
     */
    inline bool is_frame_boundary(const APIFunction&         in_function,
                                  const uint32_t&            in_n_arguments,
                                  const APIFunctionArgument* in_arguments_ptr)
    {
        bool result = (in_function == APIFUNCTION_GDI32_SWAPBUFFERS             ||
                       in_function == APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_FLIP ||
                       in_function == APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT);

        if (in_function == APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLT     ||
            in_function == APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLTFAST)
        {
            result = (in_n_arguments > D3D7_BLT_PRESENTS_ARGUMENT)                 &&
                     (in_arguments_ptr[D3D7_BLT_PRESENTS_ARGUMENT].get_u32() != 0);
        }

        return result;
    }
}

#endif /* COMMON_FRAME_BOUNDARY_H */

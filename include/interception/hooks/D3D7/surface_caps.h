/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What the caps of a D3D7 surface say about it.
 */
#ifndef D3D7_SURFACE_CAPS_H
#define D3D7_SURFACE_CAPS_H

#include "interception/hooks/D3D7/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace D3D7
        {
            class SurfaceCaps
            {
            public:
                /* Tells if the surface is the primary one, which is what the screen shows (the caps of the surface say so). The blit of a
                 * frame to it ends the frame.
                 */
                static bool is_primary_surface(IDirectDrawSurface7* in_surface_ptr);
            };
        }
    }
}

#endif /* D3D7_SURFACE_CAPS_H */

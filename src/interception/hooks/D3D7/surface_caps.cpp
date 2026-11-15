/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/hooks/common/vtable_registry.h"
#include "interception/hooks/D3D7/surface_caps.h"

bool Interception::Hooks::D3D7::SurfaceCaps::is_primary_surface(IDirectDrawSurface7* in_surface_ptr)
{
    constexpr uint32_t CAPS_PRIMARY_SURFACE = 0x00000200;

    DDSCAPS2   caps                  = {};
    const auto get_caps_func_ptr     = reinterpret_cast<PFN_IDIRECTDRAWSURFACE7_GETCAPS>(
                                           Interception::Hooks::Common::VTableRegistry::get_ptr()->get_original_function_ptr(in_surface_ptr,
                                                                                                                             VTABLE_INDEX_IDIRECTDRAWSURFACE7_GETCAPS) );
    bool       result                = false;

    if (get_caps_func_ptr != nullptr)
    {
        if (SUCCEEDED(get_caps_func_ptr(in_surface_ptr,
                                       &caps) ) )
        {
            result = ((caps.dwCaps & CAPS_PRIMARY_SURFACE) != 0);
        }
    }

    return result;
}

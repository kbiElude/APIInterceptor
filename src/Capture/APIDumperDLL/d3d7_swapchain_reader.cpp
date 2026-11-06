/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <Windows.h>
#include "Common/vtable.h"
#include "Interception/Core/D3D7Utils/constants.h"
#include "d3d7_swapchain_reader.h"

bool Capture::APIDumperDLL::D3D7SwapchainReader::get_source_format(const Interception::Hooks::D3D7::DDPIXELFORMAT& in_pixel_format,
                                                                   PixelConverter::SourceFormat*                   out_source_format_ptr)
{
    constexpr uint32_t BIT_COUNT_16        = 16;
    constexpr uint32_t BIT_COUNT_32        = 32;

    constexpr uint32_t MASK_ALPHA_A1R5G5B5 = 0x00008000;
    constexpr uint32_t MASK_ALPHA_A8R8G8B8 = 0xff000000;
    constexpr uint32_t MASK_BLUE_5_BITS    = 0x0000001f;
    constexpr uint32_t MASK_BLUE_8_BITS    = 0x000000ff;
    constexpr uint32_t MASK_GREEN_R5G6B5   = 0x000007e0;
    constexpr uint32_t MASK_GREEN_X1R5G5B5 = 0x000003e0;
    constexpr uint32_t MASK_GREEN_X8R8G8B8 = 0x0000ff00;
    constexpr uint32_t MASK_RED_R5G6B5     = 0x0000f800;
    constexpr uint32_t MASK_RED_X1R5G5B5   = 0x00007c00;
    constexpr uint32_t MASK_RED_X8R8G8B8   = 0x00ff0000;

    bool result = true;

    if (in_pixel_format.dwRGBBitCount == BIT_COUNT_32        &&
        in_pixel_format.dwRBitMask    == MASK_RED_X8R8G8B8   &&
        in_pixel_format.dwGBitMask    == MASK_GREEN_X8R8G8B8 &&
        in_pixel_format.dwBBitMask    == MASK_BLUE_8_BITS)
    {
        *out_source_format_ptr = (in_pixel_format.dwRGBAlphaBitMask == MASK_ALPHA_A8R8G8B8) ? PixelConverter::SourceFormat::A8R8G8B8
                                                                                           : PixelConverter::SourceFormat::X8R8G8B8;
    }
    else
    if (in_pixel_format.dwRGBBitCount == BIT_COUNT_16      &&
        in_pixel_format.dwRBitMask    == MASK_RED_R5G6B5   &&
        in_pixel_format.dwGBitMask    == MASK_GREEN_R5G6B5 &&
        in_pixel_format.dwBBitMask    == MASK_BLUE_5_BITS)
    {
        *out_source_format_ptr = PixelConverter::SourceFormat::R5G6B5;
    }
    else
    if (in_pixel_format.dwRGBBitCount == BIT_COUNT_16        &&
        in_pixel_format.dwRBitMask    == MASK_RED_X1R5G5B5   &&
        in_pixel_format.dwGBitMask    == MASK_GREEN_X1R5G5B5 &&
        in_pixel_format.dwBBitMask    == MASK_BLUE_5_BITS)
    {
        *out_source_format_ptr = (in_pixel_format.dwRGBAlphaBitMask == MASK_ALPHA_A1R5G5B5) ? PixelConverter::SourceFormat::A1R5G5B5
                                                                                           : PixelConverter::SourceFormat::X1R5G5B5;
    }
    else
    {
        result = false;
    }

    return result;
}

bool Capture::APIDumperDLL::D3D7SwapchainReader::read_back_buffer(void*                    in_primary_surface_ptr,
                                                                  std::array<uint32_t, 2>* out_extents_u32vec2_ptr,
                                                                  std::vector<uint8_t>*    out_rgba_u8_vec_ptr)
{
    Interception::Hooks::D3D7::IDirectDrawSurface7* back_buffer_ptr = nullptr;
    Interception::Hooks::D3D7::DDSCAPS2             caps            = {};
    bool                                            result          = false;

    const auto get_attached_func = APIInterceptor::get_method_ptr<Interception::Hooks::D3D7::PFN_IDIRECTDRAWSURFACE7_GETATTACHEDSURFACE>(in_primary_surface_ptr,
                                                                                                                                         Interception::Hooks::D3D7::VTABLE_INDEX_IDIRECTDRAWSURFACE7_GETATTACHEDSURFACE);

    caps.dwCaps = static_cast<DWORD>(Interception::Core::D3D7Utils::DDSCAPS_BACKBUFFER);

    if (FAILED(get_attached_func(static_cast<Interception::Hooks::D3D7::IDirectDrawSurface7*>(in_primary_surface_ptr),
                                &caps,
                                &back_buffer_ptr) ))
    {
        goto end;
    }

    result = read_surface(back_buffer_ptr,
                          out_extents_u32vec2_ptr,
                          out_rgba_u8_vec_ptr);

end:
    /* GetAttachedSurface gives a reference. */
    if (back_buffer_ptr != nullptr)
    {
        const auto release_func = APIInterceptor::get_method_ptr<Interception::Hooks::D3D7::PFN_IDIRECTDRAWSURFACE7_RELEASE>(back_buffer_ptr,
                                                                                                                              Interception::Hooks::D3D7::VTABLE_INDEX_IDIRECTDRAWSURFACE7_RELEASE);

        release_func(back_buffer_ptr);
    }

    return result;
}

bool Capture::APIDumperDLL::D3D7SwapchainReader::read_surface(void*                    in_surface_ptr,
                                                              std::array<uint32_t, 2>* out_extents_u32vec2_ptr,
                                                              std::vector<uint8_t>*    out_rgba_u8_vec_ptr)
{
    constexpr uint32_t LOCK_READ_ONLY = 0x00000010; /* DDLOCK_READONLY */
    constexpr uint32_t LOCK_WAIT      = 0x00000001; /* DDLOCK_WAIT     */

    Interception::Hooks::D3D7::DDSURFACEDESC2 description   = {};
    bool                                      is_locked     = false;
    bool                                      result        = false;
    PixelConverter::SourceFormat              source_format = PixelConverter::SourceFormat::A8R8G8B8;

    const auto surface_ptr = static_cast<Interception::Hooks::D3D7::IDirectDrawSurface7*>(in_surface_ptr);
    const auto lock_func   = APIInterceptor::get_method_ptr<Interception::Hooks::D3D7::PFN_IDIRECTDRAWSURFACE7_LOCK>  (in_surface_ptr,
                                                                                                                       Interception::Hooks::D3D7::VTABLE_INDEX_IDIRECTDRAWSURFACE7_LOCK);
    const auto unlock_func = APIInterceptor::get_method_ptr<Interception::Hooks::D3D7::PFN_IDIRECTDRAWSURFACE7_UNLOCK>(in_surface_ptr,
                                                                                                                       Interception::Hooks::D3D7::VTABLE_INDEX_IDIRECTDRAWSURFACE7_UNLOCK);

    description.dwSize = static_cast<DWORD>(sizeof(description) );

    if (FAILED(lock_func(surface_ptr,
                         nullptr,
                        &description,
                         LOCK_READ_ONLY | LOCK_WAIT,
                         nullptr) ))
    {
        goto end;
    }

    is_locked = true;

    if (description.lpSurface == nullptr)
    {
        goto end;
    }

    if (get_source_format(description.ddpfPixelFormat,
                         &source_format) == false)
    {
        goto end;
    }

    PixelConverter::convert_to_rgba8_bottom_first(source_format,
                                                  description.lpSurface,
                                                  static_cast<uint32_t>(description.lPitch),
                                                  description.dwWidth,
                                                  description.dwHeight,
                                                  out_rgba_u8_vec_ptr);

    (*out_extents_u32vec2_ptr)[0] = description.dwWidth;
    (*out_extents_u32vec2_ptr)[1] = description.dwHeight;

    result = true;
end:
    if (is_locked)
    {
        unlock_func(surface_ptr,
                    nullptr);
    }

    return result;
}

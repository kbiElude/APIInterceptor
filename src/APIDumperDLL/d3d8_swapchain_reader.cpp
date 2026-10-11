/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "D3D8/types.h"
#include "d3d8_swapchain_reader.h"
#include <string.h>

bool APIDumperDLL::D3D8SwapchainReader::read(void*                    in_device_ptr,
                                             std::array<uint32_t, 2>* out_extents_u32vec2_ptr,
                                             std::vector<uint8_t>*    out_rgba_u8_vec_ptr)
{
    constexpr uint32_t A1R5G5B5_ALPHA_SHIFT = 15;
    constexpr uint32_t CHANNEL_MAX          = 255;
    constexpr uint32_t FIVE_BIT_MAX         = (1u << 5) - 1;
    constexpr uint32_t SIX_BIT_MAX          = (1u << 6) - 1;
    constexpr uint32_t X1R5G5B5_BLUE_SHIFT  = 0;
    constexpr uint32_t X1R5G5B5_GREEN_SHIFT = 5;
    constexpr uint32_t X1R5G5B5_RED_SHIFT   = 10;
    constexpr uint32_t R5G6B5_BLUE_SHIFT    = 0;
    constexpr uint32_t R5G6B5_GREEN_SHIFT   = 5;
    constexpr uint32_t R5G6B5_RED_SHIFT     = 11;
    /* A8R8G8B8 and X8R8G8B8 are stored as B, G, R, A; the output is R, G, B, A. All are 32-bit pixels. */
    constexpr uint32_t ARGB8_BLUE_OFFSET    = 0;
    constexpr uint32_t ARGB8_GREEN_OFFSET   = 1;
    constexpr uint32_t ARGB8_RED_OFFSET     = 2;
    constexpr uint32_t ARGB8_ALPHA_OFFSET   = 3;
    constexpr uint32_t RGBA8_RED_OFFSET     = 0;
    constexpr uint32_t RGBA8_GREEN_OFFSET   = 1;
    constexpr uint32_t RGBA8_BLUE_OFFSET    = 2;
    constexpr uint32_t RGBA8_ALPHA_OFFSET   = 3;

    D3D8::IDirect3DSurface8* back_buffer_ptr = nullptr;
    D3D8::D3DSURFACE_DESC    description     = {};
    D3D8::D3DLOCKED_RECT     locked_rect     = {};
    bool                     is_locked       = false;
    bool                     result          = false;
    D3D8::IDirect3DSurface8* system_ptr      = nullptr;

    void** const device_vtable = *reinterpret_cast<void***>(in_device_ptr);

    const auto get_back_buffer_func = reinterpret_cast<D3D8::PFN_IDIRECT3DDEVICE8_GETBACKBUFFER>   (device_vtable[D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_GETBACKBUFFER]);
    const auto create_image_func    = reinterpret_cast<D3D8::PFN_IDIRECT3DDEVICE8_CREATEIMAGESURFACE>(device_vtable[D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_CREATEIMAGESURFACE]);
    const auto copy_rects_func      = reinterpret_cast<D3D8::PFN_IDIRECT3DDEVICE8_COPYRECTS>        (device_vtable[D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_COPYRECTS]);

    /* Releases a surface and clears the pointer. */
    const auto release_func = [](D3D8::IDirect3DSurface8** inout_surface_ptr_ptr)
    {
        if (*inout_surface_ptr_ptr != nullptr)
        {
            void** const vtable = *reinterpret_cast<void***>(*inout_surface_ptr_ptr);

            reinterpret_cast<D3D8::PFN_IDIRECT3DSURFACE8_RELEASE>(vtable[D3D8::VTABLE_INDEX_IDIRECT3DSURFACE8_RELEASE])(*inout_surface_ptr_ptr);

            *inout_surface_ptr_ptr = nullptr;
        }
    };

    if (FAILED(get_back_buffer_func(static_cast<D3D8::IDirect3DDevice8*>(in_device_ptr),
                                    0, /* BackBuffer */
                                    D3D8::D3DBACKBUFFER_TYPE_MONO,
                                   &back_buffer_ptr) ))
    {
        goto end;
    }

    {
        void** const back_buffer_vtable = *reinterpret_cast<void***>(back_buffer_ptr);

        if (FAILED(reinterpret_cast<D3D8::PFN_IDIRECT3DSURFACE8_GETDESC>(back_buffer_vtable[D3D8::VTABLE_INDEX_IDIRECT3DSURFACE8_GETDESC])(back_buffer_ptr,
                                                                                                                                         &description) ))
        {
            goto end;
        }
    }

    /* The back buffer may not be lockable; a system memory copy of it always is. */
    if (FAILED(create_image_func(static_cast<D3D8::IDirect3DDevice8*>(in_device_ptr),
                                 description.Width,
                                 description.Height,
                                 description.Format,
                                &system_ptr) ))
    {
        goto end;
    }

    if (FAILED(copy_rects_func(static_cast<D3D8::IDirect3DDevice8*>(in_device_ptr),
                               back_buffer_ptr,
                               nullptr,
                               0,
                               system_ptr,
                               nullptr) ))
    {
        goto end;
    }

    {
        void** const system_vtable = *reinterpret_cast<void***>(system_ptr);

        if (FAILED(reinterpret_cast<D3D8::PFN_IDIRECT3DSURFACE8_LOCKRECT>(system_vtable[D3D8::VTABLE_INDEX_IDIRECT3DSURFACE8_LOCKRECT])(system_ptr,
                                                                                                                                       &locked_rect,
                                                                                                                                        nullptr,
                                                                                                                                        D3D8::D3DLOCK_READONLY) ))
        {
            goto end;
        }

        is_locked = true;

        out_rgba_u8_vec_ptr->resize(static_cast<size_t>(description.Width) * description.Height * sizeof(uint32_t));

        for (uint32_t y = 0;
                      y < description.Height;
                    ++y)
        {
            /* Rows are stored bottom first. */
            const uint8_t* source_ptr      = static_cast<const uint8_t*>(locked_rect.pBits) + static_cast<size_t>(y) * locked_rect.Pitch;
            uint8_t*       destination_ptr = out_rgba_u8_vec_ptr->data() + static_cast<size_t>(description.Height - 1 - y) * description.Width * sizeof(uint32_t);

            for (uint32_t x = 0;
                          x < description.Width;
                        ++x)
            {
                uint32_t red   = 0;
                uint32_t green = 0;
                uint32_t blue  = 0;
                uint32_t alpha = CHANNEL_MAX;

                switch (description.Format)
                {
                    case D3D8::D3DFMT_A8R8G8B8:
                    case D3D8::D3DFMT_X8R8G8B8:
                    {
                        const uint8_t* pixel_ptr = source_ptr + x * sizeof(uint32_t);

                        blue  = pixel_ptr[ARGB8_BLUE_OFFSET];
                        green = pixel_ptr[ARGB8_GREEN_OFFSET];
                        red   = pixel_ptr[ARGB8_RED_OFFSET];
                        alpha = (description.Format == D3D8::D3DFMT_A8R8G8B8) ? pixel_ptr[ARGB8_ALPHA_OFFSET]
                                                                              : CHANNEL_MAX;

                        break;
                    }

                    case D3D8::D3DFMT_A1R5G5B5:
                    case D3D8::D3DFMT_X1R5G5B5:
                    {
                        uint16_t pixel = 0;

                        memcpy(&pixel,
                               source_ptr + x * sizeof(pixel),
                               sizeof(pixel) );

                        blue  = ((pixel >> X1R5G5B5_BLUE_SHIFT)  & FIVE_BIT_MAX) * CHANNEL_MAX / FIVE_BIT_MAX;
                        green = ((pixel >> X1R5G5B5_GREEN_SHIFT) & FIVE_BIT_MAX) * CHANNEL_MAX / FIVE_BIT_MAX;
                        red   = ((pixel >> X1R5G5B5_RED_SHIFT)   & FIVE_BIT_MAX) * CHANNEL_MAX / FIVE_BIT_MAX;
                        alpha = (description.Format == D3D8::D3DFMT_A1R5G5B5) ? (((pixel >> A1R5G5B5_ALPHA_SHIFT) & 1) * CHANNEL_MAX)
                                                                              : CHANNEL_MAX;

                        break;
                    }

                    case D3D8::D3DFMT_R5G6B5:
                    {
                        uint16_t pixel = 0;

                        memcpy(&pixel,
                               source_ptr + x * sizeof(pixel),
                               sizeof(pixel) );

                        blue  = ((pixel >> R5G6B5_BLUE_SHIFT)  & FIVE_BIT_MAX) * CHANNEL_MAX / FIVE_BIT_MAX;
                        green = ((pixel >> R5G6B5_GREEN_SHIFT) & SIX_BIT_MAX)  * CHANNEL_MAX / SIX_BIT_MAX;
                        red   = ((pixel >> R5G6B5_RED_SHIFT)   & FIVE_BIT_MAX) * CHANNEL_MAX / FIVE_BIT_MAX;

                        break;
                    }

                    default:
                    {
                        goto end;
                    }
                }

                destination_ptr[x * sizeof(uint32_t) + RGBA8_RED_OFFSET]   = static_cast<uint8_t>(red);
                destination_ptr[x * sizeof(uint32_t) + RGBA8_GREEN_OFFSET] = static_cast<uint8_t>(green);
                destination_ptr[x * sizeof(uint32_t) + RGBA8_BLUE_OFFSET]  = static_cast<uint8_t>(blue);
                destination_ptr[x * sizeof(uint32_t) + RGBA8_ALPHA_OFFSET] = static_cast<uint8_t>(alpha);
            }
        }
    }

    (*out_extents_u32vec2_ptr)[0] = description.Width;
    (*out_extents_u32vec2_ptr)[1] = description.Height;

    result = true;
end:
    if (is_locked)
    {
        void** const system_vtable = *reinterpret_cast<void***>(system_ptr);

        reinterpret_cast<D3D8::PFN_IDIRECT3DSURFACE8_UNLOCKRECT>(system_vtable[D3D8::VTABLE_INDEX_IDIRECT3DSURFACE8_UNLOCKRECT])(system_ptr);
    }

    release_func(&system_ptr);
    release_func(&back_buffer_ptr);

    return result;
}

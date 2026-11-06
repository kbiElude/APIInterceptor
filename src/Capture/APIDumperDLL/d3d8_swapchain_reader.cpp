/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Hooks/D3D8/types.h"
#include "d3d8_swapchain_reader.h"
#include "pixel_converter.h"

bool Capture::APIDumperDLL::D3D8SwapchainReader::read(void*                    in_device_ptr,
                                                      std::array<uint32_t, 2>* out_extents_u32vec2_ptr,
                                                      std::vector<uint8_t>*    out_rgba_u8_vec_ptr)
{
    Interception::Hooks::D3D8::IDirect3DSurface8* back_buffer_ptr = nullptr;
    Interception::Hooks::D3D8::D3DSURFACE_DESC    description     = {};
    Interception::Hooks::D3D8::D3DLOCKED_RECT     locked_rect     = {};
    bool                                          is_locked       = false;
    bool                                          result          = false;
    PixelConverter::SourceFormat                  source_format   = PixelConverter::SourceFormat::A8R8G8B8;
    Interception::Hooks::D3D8::IDirect3DSurface8* system_ptr      = nullptr;

    void** const device_vtable = *reinterpret_cast<void***>(in_device_ptr);

    const auto create_image_func    = reinterpret_cast<Interception::Hooks::D3D8::PFN_IDIRECT3DDEVICE8_CREATEIMAGESURFACE>(device_vtable[Interception::Hooks::D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_CREATEIMAGESURFACE]);
    const auto copy_rects_func      = reinterpret_cast<Interception::Hooks::D3D8::PFN_IDIRECT3DDEVICE8_COPYRECTS>         (device_vtable[Interception::Hooks::D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_COPYRECTS]);
    const auto get_back_buffer_func = reinterpret_cast<Interception::Hooks::D3D8::PFN_IDIRECT3DDEVICE8_GETBACKBUFFER>     (device_vtable[Interception::Hooks::D3D8::VTABLE_INDEX_IDIRECT3DDEVICE8_GETBACKBUFFER]);

    /* Releases a surface and clears the pointer. */
    const auto release_func = [](Interception::Hooks::D3D8::IDirect3DSurface8** inout_surface_ptr_ptr)
    {
        if (*inout_surface_ptr_ptr != nullptr)
        {
            void** const vtable = *reinterpret_cast<void***>(*inout_surface_ptr_ptr);

            reinterpret_cast<Interception::Hooks::D3D8::PFN_IDIRECT3DSURFACE8_RELEASE>(vtable[Interception::Hooks::D3D8::VTABLE_INDEX_IDIRECT3DSURFACE8_RELEASE])(*inout_surface_ptr_ptr);

            *inout_surface_ptr_ptr = nullptr;
        }
    };

    if (FAILED(get_back_buffer_func(static_cast<Interception::Hooks::D3D8::IDirect3DDevice8*>(in_device_ptr),
                                    0, /* BackBuffer */
                                    Interception::Hooks::D3D8::D3DBACKBUFFER_TYPE_MONO,
                                   &back_buffer_ptr) ))
    {
        goto end;
    }

    {
        void** const back_buffer_vtable = *reinterpret_cast<void***>(back_buffer_ptr);

        if (FAILED(reinterpret_cast<Interception::Hooks::D3D8::PFN_IDIRECT3DSURFACE8_GETDESC>(back_buffer_vtable[Interception::Hooks::D3D8::VTABLE_INDEX_IDIRECT3DSURFACE8_GETDESC])(back_buffer_ptr,
                                                                                                                                         &description) ))
        {
            goto end;
        }
    }

    switch (description.Format)
    {
        case Interception::Hooks::D3D8::D3DFMT_A8R8G8B8:
        {
            source_format = PixelConverter::SourceFormat::A8R8G8B8;

            break;
        }

        case Interception::Hooks::D3D8::D3DFMT_X8R8G8B8:
        {
            source_format = PixelConverter::SourceFormat::X8R8G8B8;

            break;
        }

        case Interception::Hooks::D3D8::D3DFMT_A1R5G5B5:
        {
            source_format = PixelConverter::SourceFormat::A1R5G5B5;

            break;
        }

        case Interception::Hooks::D3D8::D3DFMT_X1R5G5B5:
        {
            source_format = PixelConverter::SourceFormat::X1R5G5B5;

            break;
        }

        case Interception::Hooks::D3D8::D3DFMT_R5G6B5:
        {
            source_format = PixelConverter::SourceFormat::R5G6B5;

            break;
        }

        default:
        {
            /* A format the converter cannot read. */
            goto end;
        }
    }

    /* The back buffer may not be lockable; a system memory copy of it always is. */
    if (FAILED(create_image_func(static_cast<Interception::Hooks::D3D8::IDirect3DDevice8*>(in_device_ptr),
                                 description.Width,
                                 description.Height,
                                 description.Format,
                                &system_ptr) ))
    {
        goto end;
    }

    if (FAILED(copy_rects_func(static_cast<Interception::Hooks::D3D8::IDirect3DDevice8*>(in_device_ptr),
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

        if (FAILED(reinterpret_cast<Interception::Hooks::D3D8::PFN_IDIRECT3DSURFACE8_LOCKRECT>(system_vtable[Interception::Hooks::D3D8::VTABLE_INDEX_IDIRECT3DSURFACE8_LOCKRECT])(system_ptr,
                                                                                                                                                                                 &locked_rect,
                                                                                                                                                                                  nullptr,
                                                                                                                                                                                  Interception::Hooks::D3D8::D3DLOCK_READONLY) ))
        {
            goto end;
        }

        is_locked = true;

        PixelConverter::convert_to_rgba8_bottom_first(source_format,
                                                      locked_rect.pBits,
                                                      static_cast<uint32_t>(locked_rect.Pitch),
                                                      description.Width,
                                                      description.Height,
                                                      out_rgba_u8_vec_ptr);
    }

    (*out_extents_u32vec2_ptr)[0] = description.Width;
    (*out_extents_u32vec2_ptr)[1] = description.Height;

    result = true;
end:
    if (is_locked)
    {
        void** const system_vtable = *reinterpret_cast<void***>(system_ptr);

        reinterpret_cast<Interception::Hooks::D3D8::PFN_IDIRECT3DSURFACE8_UNLOCKRECT>(system_vtable[Interception::Hooks::D3D8::VTABLE_INDEX_IDIRECT3DSURFACE8_UNLOCKRECT])(system_ptr);
    }

    release_func(&system_ptr);
    release_func(&back_buffer_ptr);

    return result;
}

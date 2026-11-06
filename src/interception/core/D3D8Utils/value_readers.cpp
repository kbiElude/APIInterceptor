/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/core/D3D8Utils/value_readers.h"
#include <string.h>

bool Interception::Core::D3D8Utils::parse_matrix(const uint8_t*                        in_data_ptr,
                                                 const size_t&                         in_n_bytes,
                                                 Interception::Hooks::D3D8::D3DMATRIX* out_matrix_ptr)
{
    bool result = false;

    if (in_n_bytes != sizeof(Interception::Hooks::D3D8::D3DMATRIX) )
    {
        goto end;
    }

    ::memcpy(out_matrix_ptr,
             in_data_ptr,
             sizeof(Interception::Hooks::D3D8::D3DMATRIX) );

    result = true;
end:
    return result;
}

bool Interception::Core::D3D8Utils::parse_present_parameters(const uint8_t*     in_data_ptr,
                                                             const size_t&      in_n_bytes,
                                                             PresentParameters* out_parameters_ptr)
{
    /* hDeviceWindow sits between the two halves of the structure, and is as wide as the pointers of the dumped process. */
    constexpr size_t N_HEAD_FIELDS = 6; /* BackBufferWidth to SwapEffect                */
    constexpr size_t N_TAIL_FIELDS = 6; /* Windowed to FullScreen_PresentationInterval */

    /* Where the fields are in their halves. */
    constexpr size_t HEAD_BACK_BUFFER_COUNT_INDEX                  = 3;
    constexpr size_t HEAD_BACK_BUFFER_FORMAT_INDEX                 = 2;
    constexpr size_t HEAD_BACK_BUFFER_HEIGHT_INDEX                 = 1;
    constexpr size_t HEAD_BACK_BUFFER_WIDTH_INDEX                  = 0;
    constexpr size_t HEAD_MULTI_SAMPLE_TYPE_INDEX                  = 4;
    constexpr size_t HEAD_SWAP_EFFECT_INDEX                        = 5;
    constexpr size_t TAIL_AUTO_DEPTH_STENCIL_FORMAT_INDEX          = 2;
    constexpr size_t TAIL_ENABLE_AUTO_DEPTH_STENCIL_INDEX          = 1;
    constexpr size_t TAIL_FLAGS_INDEX                              = 3;
    constexpr size_t TAIL_FULL_SCREEN_PRESENTATION_INTERVAL_INDEX  = 5;
    constexpr size_t TAIL_FULL_SCREEN_REFRESH_RATE_IN_HZ_INDEX     = 4;
    constexpr size_t TAIL_WINDOWED_INDEX                           = 0;

    uint32_t          head_u32vec6[N_HEAD_FIELDS] = {};
    size_t            pointer_n_bytes             = 0;
    bool              result                      = false;
    uint32_t          tail_u32vec6[N_TAIL_FIELDS] = {};
    PresentParameters value;

    if (in_n_bytes == sizeof(head_u32vec6) + sizeof(uint32_t) + sizeof(tail_u32vec6) )
    {
        pointer_n_bytes = sizeof(uint32_t);
    }
    else
    if (in_n_bytes == sizeof(head_u32vec6) + sizeof(uint64_t) + sizeof(tail_u32vec6) )
    {
        pointer_n_bytes = sizeof(uint64_t);
    }
    else
    {
        goto end;
    }

    ::memcpy(head_u32vec6,
             in_data_ptr,
             sizeof(head_u32vec6) );
    ::memcpy(tail_u32vec6,
             in_data_ptr + sizeof(head_u32vec6) + pointer_n_bytes,
             sizeof(tail_u32vec6) );

    value.auto_depth_stencil_format         = static_cast<Interception::Hooks::D3D8::D3DFORMAT>          (tail_u32vec6[TAIL_AUTO_DEPTH_STENCIL_FORMAT_INDEX]);
    value.back_buffer_count                 = head_u32vec6[HEAD_BACK_BUFFER_COUNT_INDEX];
    value.back_buffer_format                = static_cast<Interception::Hooks::D3D8::D3DFORMAT>          (head_u32vec6[HEAD_BACK_BUFFER_FORMAT_INDEX]);
    value.back_buffer_height                = head_u32vec6[HEAD_BACK_BUFFER_HEIGHT_INDEX];
    value.back_buffer_width                 = head_u32vec6[HEAD_BACK_BUFFER_WIDTH_INDEX];
    value.enable_auto_depth_stencil         = (tail_u32vec6[TAIL_ENABLE_AUTO_DEPTH_STENCIL_INDEX] != 0);
    value.flags                             = tail_u32vec6[TAIL_FLAGS_INDEX];
    value.full_screen_presentation_interval = tail_u32vec6[TAIL_FULL_SCREEN_PRESENTATION_INTERVAL_INDEX];
    value.full_screen_refresh_rate_in_hz    = tail_u32vec6[TAIL_FULL_SCREEN_REFRESH_RATE_IN_HZ_INDEX];
    value.multi_sample_type                 = static_cast<Interception::Hooks::D3D8::D3DMULTISAMPLE_TYPE>(head_u32vec6[HEAD_MULTI_SAMPLE_TYPE_INDEX]);
    value.swap_effect                       = static_cast<Interception::Hooks::D3D8::D3DSWAPEFFECT>      (head_u32vec6[HEAD_SWAP_EFFECT_INDEX]);
    value.windowed                          = (tail_u32vec6[TAIL_WINDOWED_INDEX] != 0);

    *out_parameters_ptr = value;
    result              = true;
end:
    return result;
}

bool Interception::Core::D3D8Utils::parse_viewport(const uint8_t*                           in_data_ptr,
                                                   const size_t&                            in_n_bytes,
                                                   Interception::Hooks::D3D8::D3DVIEWPORT8* out_viewport_ptr)
{
    bool result = false;

    if (in_n_bytes != sizeof(Interception::Hooks::D3D8::D3DVIEWPORT8) )
    {
        goto end;
    }

    ::memcpy(out_viewport_ptr,
             in_data_ptr,
             sizeof(Interception::Hooks::D3D8::D3DVIEWPORT8) );

    result = true;
end:
    return result;
}

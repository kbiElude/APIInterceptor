/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "D3D8/argument_factory.h"
#include "D3D8/hook_policy_helper.h"
#include "D3D8/lock_tracker.h"
#include <algorithm>

APIInterceptor::APIFunctionArgument D3D8::HookPolicyHelper::create_locked_data_argument(const void*     in_object_ptr,
                                                                                        const uint32_t& in_level)
{
    LockRecord lock_record = {};
    bool       has_data    = LockTracker::get_ptr()->get_lock(in_object_ptr,
                                                              in_level,
                                                             &lock_record);

    /* Nothing was written to a resource which was locked for reading. */
    if (has_data                                    &&
        (lock_record.flags & D3DLOCK_READONLY) != 0)
    {
        has_data = false;
    }

    return ArgumentFactory::create_chunk(has_data ? lock_record.data_ptr
                                                  : nullptr,
                                         has_data ? lock_record.n_bytes
                                                  : 0);
}

uint32_t D3D8::HookPolicyHelper::get_cube_face_level_key(const D3DCUBEMAP_FACES& in_face,
                                                         const uint32_t&         in_level)
{
    constexpr uint32_t MAX_N_LEVELS_PER_FACE = 64; /* far more than a texture can have */

    return static_cast<uint32_t>(in_face) * MAX_N_LEVELS_PER_FACE + in_level;
}

uint32_t D3D8::HookPolicyHelper::get_n_shader_function_tokens(const DWORD* in_function_ptr)
{
    constexpr uint32_t D3DSI_COMMENTSIZE_MASK  = 0x7fff0000;
    constexpr uint32_t D3DSI_COMMENTSIZE_SHIFT = 16;
    constexpr uint32_t D3DSI_INSTLENGTH_MASK   = 0x0f000000;
    constexpr uint32_t D3DSI_INSTLENGTH_SHIFT  = 24;
    constexpr uint32_t D3DSI_OPCODE_MASK       = 0x0000ffff;
    constexpr uint32_t D3DSIO_COMMENT          = 0x0000fffe;
    constexpr uint32_t D3DSIO_END              = 0x0000ffff;
    constexpr uint32_t MAX_N_TOKENS            = 16384; /* sanity limit */

    bool           is_done      = (in_function_ptr == nullptr);
    uint32_t       n_tokens     = (in_function_ptr != nullptr) ? 1 /* the version token */
                                                               : 0;

    while (is_done == false      &&
           n_tokens < MAX_N_TOKENS)
    {
        const DWORD token = in_function_ptr[n_tokens];

        if ((token & D3DSI_OPCODE_MASK) == D3DSIO_END)
        {
            /* D3DSIO_END */
            n_tokens++;
            is_done = true;
        }
        else
        if ((token & D3DSI_OPCODE_MASK) == D3DSIO_COMMENT)
        {
            /* D3DSIO_COMMENT: the size is in the token. */
            n_tokens += 1 + ((token & D3DSI_COMMENTSIZE_MASK) >> D3DSI_COMMENTSIZE_SHIFT);
        }
        else
        {
            n_tokens += 1 + ((token & D3DSI_INSTLENGTH_MASK) >> D3DSI_INSTLENGTH_SHIFT);
        }
    }

    return std::min<uint32_t>(n_tokens,
                              MAX_N_TOKENS);
}

uint32_t D3D8::HookPolicyHelper::get_n_vertex_declaration_tokens(const DWORD* in_declaration_ptr)
{
    constexpr uint32_t D3DVSD_CONSTCOUNT_MASK  = 0x1e000000;
    constexpr uint32_t D3DVSD_CONSTCOUNT_SHIFT = 25;
    constexpr uint32_t D3DVSD_END              = 0xffffffff;
    constexpr uint32_t D3DVSD_TOKENTYPE_CONST  = 4;
    constexpr uint32_t D3DVSD_TOKENTYPE_SHIFT  = 29;
    constexpr uint32_t MAX_N_TOKENS            = 16384; /* sanity limit */
    constexpr uint32_t N_TOKENS_PER_CONSTANT   = 4;     /* a constant is a vector of four floats */

    bool           is_done      = (in_declaration_ptr == nullptr);
    uint32_t       n_tokens     = 0;

    while (is_done == false      &&
           n_tokens < MAX_N_TOKENS)
    {
        const DWORD token = in_declaration_ptr[n_tokens];

        n_tokens++;

        if (token == D3DVSD_END)
        {
            is_done = true;
        }
        else
        if ((token >> D3DVSD_TOKENTYPE_SHIFT) == D3DVSD_TOKENTYPE_CONST)
        {
            n_tokens += ((token & D3DVSD_CONSTCOUNT_MASK) >> D3DVSD_CONSTCOUNT_SHIFT) * N_TOKENS_PER_CONSTANT;
        }
    }

    return std::min<uint32_t>(n_tokens,
                              MAX_N_TOKENS);
}

uint32_t D3D8::HookPolicyHelper::get_n_vertices(const D3DPRIMITIVETYPE& in_primitive_type,
                                                const uint32_t&         in_primitive_count)
{
    constexpr uint32_t LINE_N_VERTICES                = 2;
    constexpr uint32_t LINE_STRIP_N_EXTRA_VERTICES    = 1; /* strips and fans share vertices between primitives */
    constexpr uint32_t TRIANGLE_N_VERTICES            = 3;
    constexpr uint32_t TRIANGLE_STRIP_N_EXTRA_VERTICES = 2;

    uint32_t result = 0;

    switch (in_primitive_type)
    {
        case D3DPT_POINTLIST:
        {
            result = in_primitive_count;

            break;
        }

        case D3DPT_LINELIST:
        {
            result = in_primitive_count * LINE_N_VERTICES;

            break;
        }

        case D3DPT_LINESTRIP:
        {
            result = in_primitive_count + LINE_STRIP_N_EXTRA_VERTICES;

            break;
        }

        case D3DPT_TRIANGLELIST:
        {
            result = in_primitive_count * TRIANGLE_N_VERTICES;

            break;
        }

        case D3DPT_TRIANGLEFAN:
        case D3DPT_TRIANGLESTRIP:
        {
            result = in_primitive_count + TRIANGLE_STRIP_N_EXTRA_VERTICES;

            break;
        }

        default:
        {
            break;
        }
    }

    return result;
}

uint32_t D3D8::HookPolicyHelper::get_surface_region_n_bytes(const D3DFORMAT& in_format,
                                                            const uint32_t&  in_width,
                                                            const uint32_t&  in_height,
                                                            const uint32_t&  in_pitch)
{
    constexpr uint32_t BLOCK_N_PIXELS_PER_SIDE = 4; /* compressed formats are made of 4x4 blocks */
    constexpr uint32_t DXT1_BLOCK_N_BYTES      = 8;
    constexpr uint32_t DXT2_TO_5_BLOCK_N_BYTES = 16;
    constexpr uint32_t PIXEL_N_BYTES_24BIT     = 3;

    uint32_t n_block_bytes = 0;
    uint32_t n_pixel_bytes = 0;
    uint32_t n_rows        = in_height;
    uint32_t n_row_bytes   = 0;
    uint32_t result        = 0;

    switch (in_format)
    {
        case D3DFMT_DXT1:
        {
            n_block_bytes = DXT1_BLOCK_N_BYTES;

            break;
        }

        case D3DFMT_DXT2:
        case D3DFMT_DXT3:
        case D3DFMT_DXT4:
        case D3DFMT_DXT5:
        {
            n_block_bytes = DXT2_TO_5_BLOCK_N_BYTES;

            break;
        }

        case D3DFMT_A8:
        case D3DFMT_A4L4:
        case D3DFMT_L8:
        case D3DFMT_P8:
        case D3DFMT_R3G3B2:
        {
            n_pixel_bytes = sizeof(uint8_t);

            break;
        }

        case D3DFMT_A1R5G5B5:
        case D3DFMT_A4R4G4B4:
        case D3DFMT_A8L8:
        case D3DFMT_A8P8:
        case D3DFMT_A8R3G3B2:
        case D3DFMT_D15S1:
        case D3DFMT_D16:
        case D3DFMT_D16_LOCKABLE:
        case D3DFMT_L6V5U5:
        case D3DFMT_R5G6B5:
        case D3DFMT_UYVY:
        case D3DFMT_V8U8:
        case D3DFMT_X1R5G5B5:
        case D3DFMT_X4R4G4B4:
        case D3DFMT_YUY2:
        {
            n_pixel_bytes = sizeof(uint16_t);

            break;
        }

        case D3DFMT_R8G8B8:
        {
            n_pixel_bytes = PIXEL_N_BYTES_24BIT;

            break;
        }

        default:
        {
            /* 32-bit formats, and any format this code is not aware of. */
            n_pixel_bytes = sizeof(uint32_t);

            break;
        }
    }

    if (n_block_bytes != 0)
    {
        n_rows      = (in_height + BLOCK_N_PIXELS_PER_SIDE - 1) / BLOCK_N_PIXELS_PER_SIDE;
        n_row_bytes = ((in_width + BLOCK_N_PIXELS_PER_SIDE - 1) / BLOCK_N_PIXELS_PER_SIDE) * n_block_bytes;
    }
    else
    {
        n_row_bytes = in_width * n_pixel_bytes;
    }

    /* The last row is not padded up to the pitch. */
    if (n_rows != 0)
    {
        result = (n_rows - 1) * in_pitch + n_row_bytes;
    }

    return result;
}

void D3D8::HookPolicyHelper::on_box_locked(const void*           in_object_ptr,
                                           const uint32_t&       in_level,
                                           const D3DVOLUME_DESC& in_description,
                                           const D3DLOCKED_BOX*  in_locked_box_ptr,
                                           const D3DBOX*         in_box_ptr,
                                           const DWORD&          in_flags)
{
    const bool is_box_set  = (in_box_ptr != nullptr);
    LockRecord lock_record = {};

    const uint32_t depth  = (is_box_set) ? (in_box_ptr->Back   - in_box_ptr->Front)
                                         : in_description.Depth;
    const uint32_t height = (is_box_set) ? (in_box_ptr->Bottom - in_box_ptr->Top)
                                         : in_description.Height;
    const uint32_t width  = (is_box_set) ? (in_box_ptr->Right  - in_box_ptr->Left)
                                         : in_description.Width;

    /* The last slice is not padded up to the slice pitch. */
    lock_record.data_ptr = static_cast<const uint8_t*>(in_locked_box_ptr->pBits);
    lock_record.flags    = in_flags;
    lock_record.n_bytes  = (depth != 0) ? (depth - 1) * static_cast<uint32_t>(in_locked_box_ptr->SlicePitch) +
                                          get_surface_region_n_bytes(in_description.Format,
                                                                     width,
                                                                     height,
                                                                     static_cast<uint32_t>(in_locked_box_ptr->RowPitch) )
                                        : 0;

    LockTracker::get_ptr()->on_locked(in_object_ptr,
                                      in_level,
                                      lock_record);
}

void D3D8::HookPolicyHelper::on_buffer_locked(const void*     in_object_ptr,
                                              const uint32_t& in_buffer_n_bytes,
                                              const UINT&     in_offset_to_lock,
                                              const UINT&     in_size_to_lock,
                                              BYTE* const*    in_data_ptr_ptr,
                                              const DWORD&    in_flags)
{
    LockRecord     lock_record    = {};
    const uint32_t n_bytes_to_end = (in_buffer_n_bytes > in_offset_to_lock) ? in_buffer_n_bytes - in_offset_to_lock
                                                                            : 0;

    lock_record.data_ptr = *in_data_ptr_ptr;
    lock_record.flags    = in_flags;
    lock_record.n_bytes  = (in_size_to_lock != 0) ? in_size_to_lock
                                                  : n_bytes_to_end;

    LockTracker::get_ptr()->on_locked(in_object_ptr,
                                      0, /* in_level */
                                      lock_record);
}

void D3D8::HookPolicyHelper::on_rect_locked(const void*            in_object_ptr,
                                            const uint32_t&        in_level,
                                            const D3DSURFACE_DESC& in_description,
                                            const D3DLOCKED_RECT*  in_locked_rect_ptr,
                                            const RECT*            in_rect_ptr,
                                            const DWORD&           in_flags)
{
    const bool is_rect_set = (in_rect_ptr != nullptr);
    LockRecord lock_record = {};

    const uint32_t height = (is_rect_set) ? static_cast<uint32_t>(in_rect_ptr->bottom - in_rect_ptr->top)
                                          : in_description.Height;
    const uint32_t width  = (is_rect_set) ? static_cast<uint32_t>(in_rect_ptr->right  - in_rect_ptr->left)
                                          : in_description.Width;

    lock_record.data_ptr = static_cast<const uint8_t*>(in_locked_rect_ptr->pBits);
    lock_record.flags    = in_flags;
    lock_record.n_bytes  = get_surface_region_n_bytes(in_description.Format,
                                                      width,
                                                      height,
                                                      static_cast<uint32_t>(in_locked_rect_ptr->Pitch) );

    LockTracker::get_ptr()->on_locked(in_object_ptr,
                                      in_level,
                                      lock_record);
}

/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/hooks/common/argument_factory.h"
#include "interception/hooks/common/lock_capture.h"
#include "interception/hooks/common/lock_tracker.h"
#include "interception/hooks/D3D8/hook_policy_helper.h"
#include "interception/core/D3D8Utils/surface_layout.h"
#include <algorithm>

APIInterceptor::APIFunctionArgument Interception::Hooks::D3D8::HookPolicyHelper::create_locked_data_argument(const void*     in_object_ptr,
                                                                                                             const uint32_t& in_level)
{
    return Interception::Hooks::Common::create_locked_data_argument(in_object_ptr,
                                                                    in_level,
                                                                    D3DLOCK_READONLY);
}

void Interception::Hooks::D3D8::HookPolicyHelper::create_present_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                           const RECT*                          in_source_rect_ptr,
                                                                           const RECT*                          in_dest_rect_ptr,
                                                                           const RGNDATA*                       in_dirty_region_ptr)
{
    constexpr uint32_t MAX_N_RECTS = 4096; /* sanity limit */

    const uint8_t* dirty_rects_ptr = nullptr;
    uint32_t       n_dirty_rects   = 0;

    if (in_dirty_region_ptr != nullptr)
    {
        dirty_rects_ptr = reinterpret_cast<const uint8_t*>(in_dirty_region_ptr->Buffer);
        n_dirty_rects   = std::min<uint32_t>(in_dirty_region_ptr->rdh.nCount,
                                             MAX_N_RECTS);
    }

    out_arguments_ptr[0] = Interception::Hooks::Common::ArgumentFactory::create_chunk(in_source_rect_ptr,
                                                                                      static_cast<uint32_t>(sizeof(RECT) ));
    out_arguments_ptr[1] = Interception::Hooks::Common::ArgumentFactory::create_chunk(in_dest_rect_ptr,
                                                                                      static_cast<uint32_t>(sizeof(RECT) ));
    out_arguments_ptr[2] = Interception::Hooks::Common::ArgumentFactory::create_chunk(dirty_rects_ptr,
                                                                                      n_dirty_rects * static_cast<uint32_t>(sizeof(RECT) ));
}

uint32_t Interception::Hooks::D3D8::HookPolicyHelper::get_cube_face_level_key(const D3DCUBEMAP_FACES& in_face,
                                                                              const uint32_t&         in_level)
{
    constexpr uint32_t MAX_N_LEVELS_PER_FACE = 64; /* far more than a texture can have */

    return static_cast<uint32_t>(in_face) * MAX_N_LEVELS_PER_FACE + in_level;
}

uint32_t Interception::Hooks::D3D8::HookPolicyHelper::get_n_shader_function_tokens(const DWORD* in_function_ptr)
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

uint32_t Interception::Hooks::D3D8::HookPolicyHelper::get_n_vertex_declaration_tokens(const DWORD* in_declaration_ptr)
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

uint32_t Interception::Hooks::D3D8::HookPolicyHelper::get_surface_region_n_bytes(const D3DFORMAT& in_format,
                                                                                 const uint32_t&  in_width,
                                                                                 const uint32_t&  in_height,
                                                                                 const uint32_t&  in_pitch)
{
    uint32_t n_row_bytes = 0;
    uint32_t n_rows      = 0;
    uint32_t result      = 0;

    Interception::Core::D3D8Utils::get_surface_region_layout(in_format,
                                     in_width,
                                     in_height,
                                    &n_rows,
                                    &n_row_bytes);

    /* The last row is not padded up to the pitch. */
    if (n_rows != 0)
    {
        result = (n_rows - 1) * in_pitch + n_row_bytes;
    }

    return result;
}

void Interception::Hooks::D3D8::HookPolicyHelper::on_box_locked(const void*           in_object_ptr,
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

    Interception::Hooks::Common::LockTracker::get_ptr()->on_locked(in_object_ptr,
                                                                   in_level,
                                                                   lock_record);
}

void Interception::Hooks::D3D8::HookPolicyHelper::on_buffer_locked(const void*     in_object_ptr,
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

    Interception::Hooks::Common::LockTracker::get_ptr()->on_locked(in_object_ptr,
                                                                   0, /* in_level */
                                                                   lock_record);
}

void Interception::Hooks::D3D8::HookPolicyHelper::on_rect_locked(const void*            in_object_ptr,
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

    Interception::Hooks::Common::LockTracker::get_ptr()->on_locked(in_object_ptr,
                                                                   in_level,
                                                                   lock_record);
}

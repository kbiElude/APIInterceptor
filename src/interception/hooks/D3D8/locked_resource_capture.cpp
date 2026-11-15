/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/hooks/common/lock_capture.h"
#include "interception/hooks/common/lock_tracker.h"
#include "interception/hooks/D3D8/locked_resource_capture.h"
#include "interception/core/D3D8Utils/surface_layout.h"

APIInterceptor::APIFunctionArgument Interception::Hooks::D3D8::LockedResourceCapture::create_locked_data_argument(const void*     in_object_ptr,
                                                                                                                  const uint32_t& in_level)
{
    return Interception::Hooks::Common::create_locked_data_argument(in_object_ptr,
                                                                    in_level,
                                                                    D3DLOCK_READONLY);
}

uint32_t Interception::Hooks::D3D8::LockedResourceCapture::get_cube_face_level_key(const D3DCUBEMAP_FACES& in_face,
                                                                                   const uint32_t&         in_level)
{
    constexpr uint32_t MAX_N_LEVELS_PER_FACE = 64; /* far more than a texture can have */

    return static_cast<uint32_t>(in_face) * MAX_N_LEVELS_PER_FACE + in_level;
}

void Interception::Hooks::D3D8::LockedResourceCapture::on_box_locked(const void*           in_object_ptr,
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
    lock_record.n_bytes  = (depth != 0) ? (depth - 1) * static_cast<uint32_t>(in_locked_box_ptr->SlicePitch) + Interception::Core::D3D8Utils::get_surface_region_n_bytes(in_description.Format,
                                                                                                                                                                         width,
                                                                                                                                                                         height,
                                                                                                                                                                         static_cast<uint32_t>(in_locked_box_ptr->RowPitch) )
                                        : 0;

    Interception::Hooks::Common::LockTracker::get_ptr()->on_locked(in_object_ptr,
                                                                   in_level,
                                                                   lock_record);
}

void Interception::Hooks::D3D8::LockedResourceCapture::on_buffer_locked(const void*     in_object_ptr,
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

void Interception::Hooks::D3D8::LockedResourceCapture::on_rect_locked(const void*            in_object_ptr,
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
    lock_record.n_bytes  = Interception::Core::D3D8Utils::get_surface_region_n_bytes(in_description.Format,
                                                                                     width,
                                                                                     height,
                                                                                     static_cast<uint32_t>(in_locked_rect_ptr->Pitch) );

    Interception::Hooks::Common::LockTracker::get_ptr()->on_locked(in_object_ptr,
                                                                   in_level,
                                                                   lock_record);
}

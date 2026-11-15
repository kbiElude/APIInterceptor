/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/hooks/common/lock_capture.h"
#include "interception/hooks/common/lock_tracker.h"
#include "interception/hooks/common/vtable_registry.h"
#include "interception/hooks/D3D7/locked_resource_capture.h"
#include "interception/core/D3D7Utils/surface_layout.h"
#include "interception/core/D3D7Utils/vertex_format.h"

APIInterceptor::APIFunctionArgument Interception::Hooks::D3D7::LockedResourceCapture::create_locked_data_argument(const void*     in_object_ptr,
                                                                                                                  const uint32_t& in_level)
{
    constexpr uint32_t DDLOCK_READONLY = 0x00000010;

    return Interception::Hooks::Common::create_locked_data_argument(in_object_ptr,
                                                                    in_level,
                                                                    DDLOCK_READONLY);
}

void Interception::Hooks::D3D7::LockedResourceCapture::on_surface_locked(const void*           in_surface_ptr,
                                                                         const RECT*           in_rect_ptr,
                                                                         const DDSURFACEDESC2* in_locked_description_ptr,
                                                                         const DWORD&          in_flags)
{
    Interception::Hooks::Common::LockRecord lock_record = {};

    lock_record.data_ptr = static_cast<const uint8_t*>(in_locked_description_ptr->lpSurface);
    lock_record.flags    = in_flags;
    lock_record.n_bytes  = Interception::Core::D3D7Utils::SurfaceLayout::get_region_n_bytes(*in_locked_description_ptr,
                                                                                            in_rect_ptr);

    Interception::Hooks::Common::LockTracker::get_ptr()->on_locked(in_surface_ptr,
                                                                   0, /* in_level */
                                                                   lock_record);
}

void Interception::Hooks::D3D7::LockedResourceCapture::on_vertex_buffer_locked(IDirect3DVertexBuffer7* in_vertex_buffer_ptr,
                                                                               const DWORD&            in_flags,
                                                                               void* const*            in_data_ptr_ptr,
                                                                               const DWORD*            in_size_ptr)
{
    Interception::Hooks::Common::LockRecord lock_record = {};

    lock_record.data_ptr = static_cast<const uint8_t*>(*in_data_ptr_ptr);
    lock_record.flags    = in_flags;

    if (in_size_ptr != nullptr)
    {
        lock_record.n_bytes = *in_size_ptr;
    }
    else
    {
        /* The size is optional: the description of the buffer has it. */
        D3DVERTEXBUFFERDESC description              = {};
        const auto          get_description_func_ptr = reinterpret_cast<PFN_IDIRECT3DVERTEXBUFFER7_GETVERTEXBUFFERDESC>(
                                                           Interception::Hooks::Common::VTableRegistry::get_ptr()->get_original_function_ptr(in_vertex_buffer_ptr,
                                                                                                                                             VTABLE_INDEX_IDIRECT3DVERTEXBUFFER7_GETVERTEXBUFFERDESC) );

        description.dwSize = sizeof(description);

        if (get_description_func_ptr != nullptr)
        {
            get_description_func_ptr(in_vertex_buffer_ptr,
                                    &description);
        }

        lock_record.n_bytes = description.dwNumVertices * Interception::Core::D3D7Utils::VertexFormat::get_n_vertex_bytes(description.dwFVF);
    }

    Interception::Hooks::Common::LockTracker::get_ptr()->on_locked(in_vertex_buffer_ptr,
                                                                   0, /* in_level */
                                                                   lock_record);
}

/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Hooks/Common/argument_factory.h"
#include "Interception/Hooks/Common/lock_capture.h"
#include "Interception/Hooks/Common/lock_tracker.h"
#include "Interception/Hooks/Common/vtable_registry.h"
#include "Interception/Hooks/D3D7/hook_policy_helper.h"
#include "Interception/Hooks/D3D7/hook_table.h"
#include "Interception/Core/D3D7Utils/guids.h"
#include "Interception/Core/D3D7Utils/strided_layout.h"
#include "Interception/Core/D3D7Utils/surface_layout.h"
#include "Interception/Core/D3D7Utils/vertex_format.h"
#include <vector>

APIInterceptor::APIFunctionArgument Interception::Hooks::D3D7::HookPolicyHelper::create_locked_data_argument(const void*     in_object_ptr,
                                                                                                             const uint32_t& in_level)
{
    constexpr uint32_t DDLOCK_READONLY = 0x00000010;

    return Interception::Hooks::Common::create_locked_data_argument(in_object_ptr,
                                                                    in_level,
                                                                    DDLOCK_READONLY);
}

APIInterceptor::APIFunctionArgument Interception::Hooks::D3D7::HookPolicyHelper::create_strided_data_argument(const D3DDRAWPRIMITIVESTRIDEDDATA* in_strided_data_ptr,
                                                                                                              const uint32_t&                    in_vertex_format,
                                                                                                              const uint32_t&                    in_n_vertices)
{
    constexpr uint32_t DIFFUSE_ARRAY  = 2;
    constexpr uint32_t N_BYTES_COLOR  = sizeof(uint32_t);
    constexpr uint32_t N_BYTES_NORMAL = 3 * sizeof(float);
    constexpr uint32_t NORMAL_ARRAY   = 1;
    constexpr uint32_t POSITION_ARRAY = 0;
    constexpr uint32_t SPECULAR_ARRAY = 3;
    constexpr uint32_t TEXTURE_ARRAY  = 4;

    constexpr uint32_t N_ARRAYS = Interception::Core::D3D7Utils::StridedLayout::N_ARRAYS;

    const uint8_t* array_ptr_ptr_vec[N_ARRAYS] = {};
    uint32_t       array_n_bytes_vec [N_ARRAYS] = {};

    /* The last vertex is not padded up to the stride. */
    const auto set_array_func = [&](const uint32_t&        in_n_array,
                                    const D3DDP_PTRSTRIDE& in_array,
                                    const uint32_t&        in_n_element_bytes)
    {
        if (in_array.lpvData != nullptr &&
            in_n_vertices    != 0)
        {
            array_ptr_ptr_vec[in_n_array] = static_cast<const uint8_t*>(in_array.lpvData);
            array_n_bytes_vec[in_n_array] = (in_n_vertices - 1) * in_array.dwStride + in_n_element_bytes;
        }
    };

    if (in_strided_data_ptr != nullptr)
    {
        if (Interception::Core::D3D7Utils::VertexFormat::has_position(in_vertex_format) )
        {
            const uint32_t position_n_bytes = Interception::Core::D3D7Utils::VertexFormat::get_n_position_bytes(in_vertex_format);

            set_array_func(POSITION_ARRAY,
                           in_strided_data_ptr->position,
                           position_n_bytes);
        }

        if (Interception::Core::D3D7Utils::VertexFormat::has_normal(in_vertex_format) )
        {
            set_array_func(NORMAL_ARRAY,
                           in_strided_data_ptr->normal,
                           N_BYTES_NORMAL);
        }

        if (Interception::Core::D3D7Utils::VertexFormat::has_diffuse(in_vertex_format) )
        {
            set_array_func(DIFFUSE_ARRAY,
                           in_strided_data_ptr->diffuse,
                           N_BYTES_COLOR);
        }

        if (Interception::Core::D3D7Utils::VertexFormat::has_specular(in_vertex_format) )
        {
            set_array_func(SPECULAR_ARRAY,
                           in_strided_data_ptr->specular,
                           N_BYTES_COLOR);
        }

        for (uint32_t n_stage = 0;
                      n_stage < Interception::Core::D3D7Utils::VertexFormat::get_n_texture_stages(in_vertex_format);
                    ++n_stage)
        {
            const uint32_t coordinate_n_bytes = Interception::Core::D3D7Utils::VertexFormat::get_n_texture_coordinate_bytes(in_vertex_format,
                                                                                                                            n_stage);

            set_array_func(TEXTURE_ARRAY + n_stage,
                           in_strided_data_ptr->textureCoords[n_stage],
                           coordinate_n_bytes);
        }
    }

    /* The number of the arrays, their sizes, and the arrays. */
    std::vector<uint8_t> chunk_u8_vec;

    chunk_u8_vec.insert(chunk_u8_vec.end(),
                        reinterpret_cast<const uint8_t*>(&N_ARRAYS),
                        reinterpret_cast<const uint8_t*>(&N_ARRAYS) + sizeof(N_ARRAYS) );
    chunk_u8_vec.insert(chunk_u8_vec.end(),
                        reinterpret_cast<const uint8_t*>(array_n_bytes_vec),
                        reinterpret_cast<const uint8_t*>(array_n_bytes_vec) + sizeof(array_n_bytes_vec) );

    for (uint32_t n_array = 0;
                  n_array < N_ARRAYS;
                ++n_array)
    {
        if (array_ptr_ptr_vec[n_array] != nullptr)
        {
            chunk_u8_vec.insert(chunk_u8_vec.end(),
                                array_ptr_ptr_vec[n_array],
                                array_ptr_ptr_vec[n_array] + array_n_bytes_vec[n_array]);
        }
    }

    return Interception::Hooks::Common::ArgumentFactory::create_chunk(chunk_u8_vec.data(),
                                                                      static_cast<uint32_t>(chunk_u8_vec.size() ));
}

bool Interception::Hooks::D3D7::HookPolicyHelper::is_primary_surface(IDirectDrawSurface7* in_surface_ptr)
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

void Interception::Hooks::D3D7::HookPolicyHelper::on_surface_locked(const void*           in_surface_ptr,
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

void Interception::Hooks::D3D7::HookPolicyHelper::on_vertex_buffer_locked(IDirect3DVertexBuffer7* in_vertex_buffer_ptr,
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

void Interception::Hooks::D3D7::HookPolicyHelper::patch_object_for_iid(const GUID& in_iid,
                                                                       void*       in_object_ptr)
{
    const auto* known_guid_ptr = Interception::Core::D3D7Utils::find_known_guid(in_iid);

    if (in_object_ptr   != nullptr &&
        known_guid_ptr  != nullptr &&
        known_guid_ptr->interface_type != Interface::UNKNOWN)
    {
        get_hook_table_ptr()->patch_object(static_cast<uint32_t>(known_guid_ptr->interface_type),
                                           in_object_ptr);
    }
}

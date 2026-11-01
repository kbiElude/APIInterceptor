/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "Interception/Hooks/OpenGL/client_array_manager.h"
#include "Interception/Hooks/OpenGL/types.h"
#include <string.h>

/* gl/gl.h provides the compatibility-profile tokens which are absent from glcorearb.h. */
#include "gl/gl.h"

/* Compatibility-profile tokens which neither gl/gl.h nor the (core-guarded) Khronos headers provide. */
static constexpr GLenum COMPAT_GL_FOG_COORD_ARRAY       = 0x8457;
static constexpr GLenum COMPAT_GL_SECONDARY_COLOR_ARRAY = 0x845E;

/* Copies of the draw call which are bigger than this are assumed to be the result of bad arguments. */
static constexpr uint64_t MAX_SNAPSHOT_ARRAY_N_BYTES = 256ull * 1024 * 1024;

Interception::Hooks::OpenGL::ClientArrayManager::ClientArrayManager()
    :m_bound_vertex_array   (0),
     m_client_active_texture(0)
{
    /* Stub */
}

Interception::Hooks::OpenGL::ClientArrayManager::ClientArray& Interception::Hooks::OpenGL::ClientArrayManager::get_array(const ClientArrayKind& in_kind,
                                                                                                                         const uint32_t&        in_index)
{
    return m_array_map[ClientArrayKey(in_kind,
                                      in_index)];
}

uint32_t Interception::Hooks::OpenGL::ClientArrayManager::get_bound_vertex_array() const
{
    return m_bound_vertex_array;
}

uint32_t Interception::Hooks::OpenGL::ClientArrayManager::get_client_active_texture() const
{
    return m_client_active_texture;
}

uint32_t Interception::Hooks::OpenGL::ClientArrayManager::get_element_n_bytes(const int32_t&  in_size,
                                                                              const uint32_t& in_type)
{
    uint32_t n_components = static_cast<uint32_t>(in_size);
    uint32_t result       = 0;

    switch (in_type)
    {
        case GL_INT_2_10_10_10_REV:          /* fall-back */
        case GL_UNSIGNED_INT_10F_11F_11F_REV:/* fall-back */
        case GL_UNSIGNED_INT_2_10_10_10_REV:
        {
            /* Packed types are one element, whatever the size says. */
            result = sizeof(uint32_t);

            goto end;
        }

        default:
        {
            break;
        }
    }

    /* GL_BGRA is a size, too. */
    if (in_size == GL_BGRA)
    {
        n_components = 4;
    }

    result = n_components * get_n_type_bytes(in_type);
end:
    return result;
}

const Interception::Hooks::OpenGL::ClientArrayManager::InterleavedFormat* Interception::Hooks::OpenGL::ClientArrayManager::get_interleaved_format_ptr(const uint32_t& in_format)
{
    static const InterleavedFormat format_table[] =
    {
        /* color_size, color_type,       format,             has_normal, texture_size, vertex_size */
        {0,            0,                GL_V2F,             false,      0,            2},
        {0,            0,                GL_V3F,             false,      0,            3},
        {4,            GL_UNSIGNED_BYTE, GL_C4UB_V2F,        false,      0,            2},
        {4,            GL_UNSIGNED_BYTE, GL_C4UB_V3F,        false,      0,            3},
        {3,            GL_FLOAT,         GL_C3F_V3F,         false,      0,            3},
        {0,            0,                GL_N3F_V3F,         true,       0,            3},
        {4,            GL_FLOAT,         GL_C4F_N3F_V3F,     true,       0,            3},
        {0,            0,                GL_T2F_V3F,         false,      2,            3},
        {0,            0,                GL_T4F_V4F,         false,      4,            4},
        {4,            GL_UNSIGNED_BYTE, GL_T2F_C4UB_V3F,    false,      2,            3},
        {3,            GL_FLOAT,         GL_T2F_C3F_V3F,     false,      2,            3},
        {0,            0,                GL_T2F_N3F_V3F,     true,       2,            3},
        {4,            GL_FLOAT,         GL_T2F_C4F_N3F_V3F, true,       2,            3},
        {4,            GL_FLOAT,         GL_T4F_C4F_N3F_V4F, true,       4,            4},
    };

    const InterleavedFormat* result_ptr = nullptr;

    for (const auto& current_format : format_table)
    {
        if (current_format.format == in_format)
        {
            result_ptr = &current_format;

            break;
        }
    }

    return result_ptr;
}

bool Interception::Hooks::OpenGL::ClientArrayManager::get_kind_for_array_enum(const uint32_t&  in_array,
                                                                              ClientArrayKind* out_kind_ptr)
{
    bool result = true;

    switch (in_array)
    {
        case COMPAT_GL_FOG_COORD_ARRAY:       *out_kind_ptr = ClientArrayKind::FOG_COORD;       break;
        case COMPAT_GL_SECONDARY_COLOR_ARRAY: *out_kind_ptr = ClientArrayKind::SECONDARY_COLOR; break;
        case GL_COLOR_ARRAY:                  *out_kind_ptr = ClientArrayKind::COLOR;           break;
        case GL_EDGE_FLAG_ARRAY:              *out_kind_ptr = ClientArrayKind::EDGE_FLAG;       break;
        case GL_INDEX_ARRAY:                  *out_kind_ptr = ClientArrayKind::INDEX;           break;
        case GL_NORMAL_ARRAY:                 *out_kind_ptr = ClientArrayKind::NORMAL;          break;
        case GL_TEXTURE_COORD_ARRAY:          *out_kind_ptr = ClientArrayKind::TEX_COORD;       break;
        case GL_VERTEX_ARRAY:                 *out_kind_ptr = ClientArrayKind::VERTEX;          break;

        default:
        {
            result = false;
        }
    }

    return result;
}

uint32_t Interception::Hooks::OpenGL::ClientArrayManager::get_n_type_bytes(const uint32_t& in_type)
{
    uint32_t result = 0;

    switch (in_type)
    {
        case GL_BYTE:           result = 1;                  break;
        case GL_DOUBLE:         result = sizeof(double);     break;
        case GL_FIXED:          result = sizeof(int32_t);    break;
        case GL_FLOAT:          result = sizeof(float);      break;
        case GL_HALF_FLOAT:     result = sizeof(uint16_t);   break;
        case GL_INT:            result = sizeof(int32_t);    break;
        case GL_SHORT:          result = sizeof(int16_t);    break;
        case GL_UNSIGNED_BYTE:  result = 1;                  break;
        case GL_UNSIGNED_INT:   result = sizeof(uint32_t);   break;
        case GL_UNSIGNED_SHORT: result = sizeof(uint16_t);   break;

        default:
        {
            AI_FAIL_UNSUPPORTED(in_type);
        }
    }

    return result;
}

bool Interception::Hooks::OpenGL::ClientArrayManager::has_client_arrays() const
{
    bool result = false;

    if (m_bound_vertex_array == 0)
    {
        for (const auto& current_entry : m_array_map)
        {
            if (is_client_array(current_entry.second) )
            {
                result = true;

                break;
            }
        }
    }

    return result;
}

bool Interception::Hooks::OpenGL::ClientArrayManager::is_client_array(const ClientArray& in_array)
{
    return (in_array.is_enabled   &&
            in_array.array_buffer == 0 &&
            in_array.pointer_ptr  != nullptr);
}

void Interception::Hooks::OpenGL::ClientArrayManager::set_bound_vertex_array(const uint32_t& in_vertex_array)
{
    m_bound_vertex_array = in_vertex_array;
}

void Interception::Hooks::OpenGL::ClientArrayManager::set_client_active_texture(const uint32_t& in_texture_unit)
{
    m_client_active_texture = in_texture_unit;
}

void Interception::Hooks::OpenGL::ClientArrayManager::set_divisor(const uint32_t& in_index,
                                                                  const uint32_t& in_divisor)
{
    if (m_bound_vertex_array == 0)
    {
        get_array(ClientArrayKind::GENERIC,
                  in_index).divisor = in_divisor;
    }
}

void Interception::Hooks::OpenGL::ClientArrayManager::set_enabled(const ClientArrayKind& in_kind,
                                                                  const uint32_t&        in_index,
                                                                  const bool&            in_is_enabled)
{
    if (m_bound_vertex_array == 0)
    {
        get_array(in_kind,
                  in_index).is_enabled = in_is_enabled;
    }
}

void Interception::Hooks::OpenGL::ClientArrayManager::set_interleaved_arrays(const uint32_t& in_format,
                                                                             const int32_t&  in_stride,
                                                                             const void*     in_pointer_ptr,
                                                                             const uint32_t& in_array_buffer)
{
    const auto format_ptr = get_interleaved_format_ptr(in_format);

    if (format_ptr == nullptr)
    {
        AI_ASSERT_FAIL();

        goto end;
    }

    if (m_bound_vertex_array != 0)
    {
        goto end;
    }

    {
        const uint32_t n_color_bytes   = format_ptr->color_size * ((format_ptr->color_type == GL_FLOAT) ? sizeof(float) : 1);
        const uint32_t n_normal_bytes  = format_ptr->has_normal ? 3 * sizeof(float) : 0;
        const uint32_t n_texture_bytes = format_ptr->texture_size * sizeof(float);
        const uint32_t n_vertex_bytes  = format_ptr->vertex_size * sizeof(float);
        const int32_t  stride          = (in_stride != 0) ? in_stride
                                                          : static_cast<int32_t>(n_color_bytes + n_normal_bytes + n_texture_bytes + n_vertex_bytes);
        const auto     base_ptr        = static_cast<const uint8_t*>(in_pointer_ptr);
        const auto     texture_unit    = m_client_active_texture;
        uint32_t       offset          = 0;

        /* The call disables what the format does not have, and the arrays which it never has. */
        set_enabled(ClientArrayKind::EDGE_FLAG,
                    0,
                    false);
        set_enabled(ClientArrayKind::INDEX,
                    0,
                    false);

        set_enabled(ClientArrayKind::TEX_COORD,
                    texture_unit,
                    format_ptr->texture_size != 0);

        if (format_ptr->texture_size != 0)
        {
            set_pointer(ClientArrayKind::TEX_COORD,
                        texture_unit,
                        static_cast<int32_t>(format_ptr->texture_size),
                        GL_FLOAT,
                        stride,
                        base_ptr + offset,
                        in_array_buffer,
                        false,  /* in_is_integer    */
                        false,  /* in_is_long       */
                        false); /* in_is_normalized */

            offset += n_texture_bytes;
        }

        set_enabled(ClientArrayKind::COLOR,
                    0,
                    format_ptr->color_size != 0);

        if (format_ptr->color_size != 0)
        {
            set_pointer(ClientArrayKind::COLOR,
                        0,
                        static_cast<int32_t>(format_ptr->color_size),
                        format_ptr->color_type,
                        stride,
                        base_ptr + offset,
                        in_array_buffer,
                        false,  /* in_is_integer    */
                        false,  /* in_is_long       */
                        false); /* in_is_normalized */

            offset += n_color_bytes;
        }

        set_enabled(ClientArrayKind::NORMAL,
                    0,
                    format_ptr->has_normal);

        if (format_ptr->has_normal)
        {
            set_pointer(ClientArrayKind::NORMAL,
                        0,
                        3,
                        GL_FLOAT,
                        stride,
                        base_ptr + offset,
                        in_array_buffer,
                        false,  /* in_is_integer    */
                        false,  /* in_is_long       */
                        false); /* in_is_normalized */

            offset += n_normal_bytes;
        }

        set_enabled(ClientArrayKind::VERTEX,
                    0,
                    true);
        set_pointer(ClientArrayKind::VERTEX,
                    0,
                    static_cast<int32_t>(format_ptr->vertex_size),
                    GL_FLOAT,
                    stride,
                    base_ptr + offset,
                    in_array_buffer,
                    false,  /* in_is_integer    */
                    false,  /* in_is_long       */
                    false); /* in_is_normalized */
    }

end:
    ;
}

void Interception::Hooks::OpenGL::ClientArrayManager::set_pointer(const ClientArrayKind& in_kind,
                                                                  const uint32_t&        in_index,
                                                                  const int32_t&         in_size,
                                                                  const uint32_t&        in_type,
                                                                  const int32_t&         in_stride,
                                                                  const void*            in_pointer_ptr,
                                                                  const uint32_t&        in_array_buffer,
                                                                  const bool&            in_is_integer,
                                                                  const bool&            in_is_long,
                                                                  const bool&            in_is_normalized)
{
    if (m_bound_vertex_array == 0)
    {
        auto& array = get_array(in_kind,
                                in_index);

        array.array_buffer  = in_array_buffer;
        array.is_integer    = in_is_integer;
        array.is_long       = in_is_long;
        array.is_normalized = in_is_normalized;
        array.pointer_ptr   = in_pointer_ptr;
        array.size          = in_size;
        array.stride        = in_stride;
        array.type          = in_type;
    }
}

std::vector<uint8_t> Interception::Hooks::OpenGL::ClientArrayManager::take_snapshot(const int64_t&  in_first_element,
                                                                                    const int64_t&  in_n_elements,
                                                                                    const uint32_t& in_instance_count,
                                                                                    const uint32_t& in_base_instance) const
{
    uint32_t             n_arrays = 0;
    std::vector<uint8_t> result_u8_vec;

    /* Appends the bytes to the end of the vector. */
    const auto append_bytes_func = [&](const void*  in_data_ptr,
                                       const size_t& in_n_bytes)
    {
        result_u8_vec.insert(result_u8_vec.end(),
                             static_cast<const uint8_t*>(in_data_ptr),
                             static_cast<const uint8_t*>(in_data_ptr) + in_n_bytes);
    };

    /* Appends the value to the end of the vector. */
    const auto append_value_func = [&](const auto& in_value)
    {
        append_bytes_func(&in_value,
                          sizeof(in_value) );
    };

    if (has_client_arrays() == false)
    {
        goto end;
    }

    /* The array count is only known when the arrays have been through; it is put in place at the end. */
    result_u8_vec.resize(sizeof(uint32_t) );

    for (const auto& current_entry : m_array_map)
    {
        const auto& array = current_entry.second;

        if (is_client_array(array) == false)
        {
            continue;
        }

        {
            const uint32_t divisor         = array.divisor;
            const int64_t  first_element   = (divisor == 0) ? in_first_element
                                                            : static_cast<int64_t>(in_base_instance);
            const int64_t  n_elements      = (divisor == 0) ? in_n_elements
                                                            : (static_cast<int64_t>(in_instance_count) + divisor - 1) / divisor;
            const uint32_t element_n_bytes = get_element_n_bytes(array.size,
                                                                 array.type);
            const uint64_t stride_n_bytes  = (array.stride != 0) ? static_cast<uint64_t>(array.stride)
                                                                 : element_n_bytes;
            uint64_t       n_bytes         = 0;

            if (n_elements <= 0 ||
                first_element < 0)
            {
                continue;
            }

            n_bytes = (static_cast<uint64_t>(n_elements) - 1) * stride_n_bytes + element_n_bytes;

            if (n_bytes > MAX_SNAPSHOT_ARRAY_N_BYTES)
            {
                AI_ASSERT_FAIL();

                continue;
            }

            {
                const uint32_t kind          = static_cast<uint32_t>(current_entry.first.first);
                const uint32_t index         = current_entry.first.second;
                const int32_t  size          = array.size;
                const uint32_t type          = array.type;
                const uint32_t stride        = static_cast<uint32_t>(array.stride);
                const uint32_t flags         = (array.is_integer    ? SNAPSHOT_FLAG_IS_INTEGER    : 0) |
                                               (array.is_long       ? SNAPSHOT_FLAG_IS_LONG       : 0) |
                                               (array.is_normalized ? SNAPSHOT_FLAG_IS_NORMALIZED : 0);
                const uint64_t pointer       = static_cast<uint64_t>(reinterpret_cast<uintptr_t>(array.pointer_ptr) );
                const uint32_t n_elements_32 = static_cast<uint32_t>(n_elements);
                const uint32_t first_32      = static_cast<uint32_t>(first_element);
                const uint32_t n_bytes_32    = static_cast<uint32_t>(n_bytes);
                const auto     data_ptr      = static_cast<const uint8_t*>(array.pointer_ptr) + static_cast<uint64_t>(first_element) * stride_n_bytes;

                append_value_func(kind);
                append_value_func(index);
                append_value_func(size);
                append_value_func(type);
                append_value_func(stride);
                append_value_func(flags);
                append_value_func(divisor);
                append_value_func(pointer);
                append_value_func(first_32);
                append_value_func(n_elements_32);
                append_value_func(n_bytes_32);
                append_bytes_func(data_ptr,
                                  n_bytes_32);

                n_arrays++;
            }
        }
    }

    if (n_arrays == 0)
    {
        result_u8_vec.clear();

        goto end;
    }

    ::memcpy(result_u8_vec.data(),
            &n_arrays,
             sizeof(n_arrays) );

end:
    return result_u8_vec;
}

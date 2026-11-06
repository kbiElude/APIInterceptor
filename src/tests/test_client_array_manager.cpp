/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the tracking of the vertex arrays which live in the app's memory, and of the snapshots taken of them.
 */
#include <gtest/gtest.h>
#include "interception/hooks/OpenGL/client_array_manager.h"
#include "interception/hooks/OpenGL/types.h"
#include "gl/gl.h"
#include <string.h>
#include <vector>

/* One array of a snapshot, as stored. */
struct SnapshotArray
{
    std::vector<uint8_t> data_u8_vec;
    uint32_t             divisor;
    uint32_t             first_element;
    uint32_t             flags;
    uint32_t             index;
    uint32_t             kind;
    uint32_t             n_elements;
    uint64_t             pointer;
    int32_t              size;
    uint32_t             stride;
    uint32_t             type;
};

static std::vector<SnapshotArray> parse_snapshot(const std::vector<uint8_t>& in_snapshot_u8_vec)
{
    size_t                     offset = 0;
    std::vector<SnapshotArray> result_vec;

    const auto read_func = [&](void*         out_data_ptr,
                               const size_t& in_n_bytes)
    {
        ::memcpy(out_data_ptr,
                 in_snapshot_u8_vec.data() + offset,
                 in_n_bytes);

        offset += in_n_bytes;
    };

    const auto read_value_func = [&](auto* out_value_ptr)
    {
        read_func(out_value_ptr,
                  sizeof(*out_value_ptr) );
    };

    if (in_snapshot_u8_vec.empty() == false)
    {
        uint32_t n_arrays = 0;

        read_value_func(&n_arrays);

        for (uint32_t n_array = 0;
                      n_array < n_arrays;
                    ++n_array)
        {
            SnapshotArray array;
            uint32_t      n_bytes = 0;

            read_value_func(&array.kind);
            read_value_func(&array.index);
            read_value_func(&array.size);
            read_value_func(&array.type);
            read_value_func(&array.stride);
            read_value_func(&array.flags);
            read_value_func(&array.divisor);
            read_value_func(&array.pointer);
            read_value_func(&array.first_element);
            read_value_func(&array.n_elements);
            read_value_func(&n_bytes);

            array.data_u8_vec.resize(n_bytes);

            read_func(array.data_u8_vec.data(),
                      n_bytes);

            result_vec.push_back(array);
        }

        EXPECT_EQ(offset,
                  in_snapshot_u8_vec.size() );
    }

    return result_vec;
}

TEST(ClientArrayManager, CopiesTheRangeOfAnEnabledClientArray)
{
    const float vertices_fp32vec12[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    Interception::Hooks::OpenGL::ClientArrayManager state;

    state.set_pointer(Interception::Hooks::OpenGL::ClientArrayKind::VERTEX,
                      0,
                      3,
                      GL_FLOAT,
                      0,
                      vertices_fp32vec12,
                      0,
                      false,  /* in_is_integer    */
                      false,  /* in_is_long       */
                      false); /* in_is_normalized */
    state.set_enabled(Interception::Hooks::OpenGL::ClientArrayKind::VERTEX,
                      0,
                      true);  /* in_is_enabled */

    EXPECT_TRUE(state.has_client_arrays() );

    /* Elements 1 and 2 of 3 floats each. */
    const auto array_vec = parse_snapshot(state.take_snapshot(1,
                                                              2,
                                                              1,
                                                              0) );

    ASSERT_EQ(array_vec.size(),
              1u);
    EXPECT_EQ(array_vec[0].kind,
              static_cast<uint32_t>(Interception::Hooks::OpenGL::ClientArrayKind::VERTEX) );
    EXPECT_EQ(array_vec[0].first_element,
              1u);
    EXPECT_EQ(array_vec[0].n_elements,
              2u);
    EXPECT_EQ(array_vec[0].data_u8_vec.size(),
              6 * sizeof(float) );
    EXPECT_EQ(::memcmp(array_vec[0].data_u8_vec.data(),
                       vertices_fp32vec12 + 3,
                       6 * sizeof(float) ),
              0);
}

TEST(ClientArrayManager, HonoursTheStride)
{
    const uint8_t data_u8vec32[32] = {};

    Interception::Hooks::OpenGL::ClientArrayManager state;

    state.set_pointer(Interception::Hooks::OpenGL::ClientArrayKind::COLOR,
                      0,
                      4,
                      GL_UNSIGNED_BYTE,
                      16,
                      data_u8vec32,
                      0,
                      false,  /* in_is_integer    */
                      false,  /* in_is_long       */
                      false); /* in_is_normalized */
    state.set_enabled(Interception::Hooks::OpenGL::ClientArrayKind::COLOR,
                      0,
                      true);  /* in_is_enabled */

    /* Two elements: the second one starts 16 bytes after the first, and is 4 bytes long. */
    const auto array_vec = parse_snapshot(state.take_snapshot(0,
                                                              2,
                                                              1,
                                                              0) );

    ASSERT_EQ(array_vec.size(),
              1u);
    EXPECT_EQ(array_vec[0].data_u8_vec.size(),
              20u);
    EXPECT_EQ(array_vec[0].stride,
              16u);
}

TEST(ClientArrayManager, IgnoresArraysInBuffersAndDisabledArrays)
{
    const float data_fp32vec4[] = {1, 2, 3, 4};

    Interception::Hooks::OpenGL::ClientArrayManager state;

    /* In a buffer. */
    state.set_pointer(Interception::Hooks::OpenGL::ClientArrayKind::VERTEX,
                      0,
                      4,
                      GL_FLOAT,
                      0,
                      nullptr,
                      5,      /* in_array_buffer */
                      false,  /* in_is_integer    */
                      false,  /* in_is_long       */
                      false); /* in_is_normalized */
    state.set_enabled(Interception::Hooks::OpenGL::ClientArrayKind::VERTEX,
                      0,
                      true);  /* in_is_enabled */

    /* Not enabled. */
    state.set_pointer(Interception::Hooks::OpenGL::ClientArrayKind::NORMAL,
                      0,
                      3,
                      GL_FLOAT,
                      0,
                      data_fp32vec4,
                      0,      /* in_array_buffer */
                      false,  /* in_is_integer    */
                      false,  /* in_is_long       */
                      false); /* in_is_normalized */

    EXPECT_FALSE(state.has_client_arrays() );
    EXPECT_TRUE(state.take_snapshot(0,
                                    1,
                                    1,
                                    0).empty() );
}

TEST(ClientArrayManager, ArraysWithADivisorAreReadByInstance)
{
    const float data_fp32vec16[16] = {};

    Interception::Hooks::OpenGL::ClientArrayManager state;

    state.set_pointer(Interception::Hooks::OpenGL::ClientArrayKind::GENERIC,
                      2,
                      4,
                      GL_FLOAT,
                      0,
                      data_fp32vec16,
                      0,
                      false,  /* in_is_integer    */
                      false,  /* in_is_long       */
                      true);  /* in_is_normalized */
    state.set_enabled(Interception::Hooks::OpenGL::ClientArrayKind::GENERIC,
                      2,
                      true);  /* in_is_enabled */
    state.set_divisor(2,
                      2);

    /* 5 instances with a divisor of 2 read 3 elements, from the base instance. */
    const auto array_vec = parse_snapshot(state.take_snapshot(100,
                                                              4,
                                                              5,
                                                              1) );

    ASSERT_EQ(array_vec.size(),
              1u);
    EXPECT_EQ(array_vec[0].index,
              2u);
    EXPECT_EQ(array_vec[0].first_element,
              1u);
    EXPECT_EQ(array_vec[0].n_elements,
              3u);
    EXPECT_EQ(array_vec[0].divisor,
              2u);
    EXPECT_EQ(array_vec[0].flags,
              Interception::Hooks::OpenGL::ClientArrayManager::SNAPSHOT_FLAG_IS_NORMALIZED);
}

TEST(ClientArrayManager, NothingIsTrackedWhileAVertexArrayIsBound)
{
    const float data_fp32vec4[] = {1, 2, 3, 4};

    Interception::Hooks::OpenGL::ClientArrayManager state;

    state.set_bound_vertex_array(7);
    state.set_pointer(Interception::Hooks::OpenGL::ClientArrayKind::VERTEX,
                      0,
                      4,
                      GL_FLOAT,
                      0,
                      data_fp32vec4,
                      0,
                      false,  /* in_is_integer    */
                      false,  /* in_is_long       */
                      false); /* in_is_normalized */
    state.set_enabled(Interception::Hooks::OpenGL::ClientArrayKind::VERTEX,
                      0,
                      true);  /* in_is_enabled */
    state.set_bound_vertex_array(0);

    EXPECT_FALSE(state.has_client_arrays() );
}

TEST(ClientArrayManager, InterleavedArraysSetUpEveryArrayOfTheFormat)
{
    /* Texture coordinates (2 floats), a color (4 bytes), a vertex (3 floats): 24 bytes per element. */
    const uint8_t data_u8vec48[48] = {};

    Interception::Hooks::OpenGL::ClientArrayManager state;

    state.set_interleaved_arrays(GL_T2F_C4UB_V3F,
                                 0,
                                 data_u8vec48,
                                 0);

    const auto array_vec = parse_snapshot(state.take_snapshot(0,
                                                              2,
                                                              1,
                                                              0) );

    ASSERT_EQ(array_vec.size(),
              3u);

    /* The map is ordered by kind: colors, texture coordinates, vertices. */
    EXPECT_EQ(array_vec[0].kind,
              static_cast<uint32_t>(Interception::Hooks::OpenGL::ClientArrayKind::COLOR) );
    EXPECT_EQ(array_vec[0].pointer,
              reinterpret_cast<uint64_t>(data_u8vec48 + 8) );
    EXPECT_EQ(array_vec[1].kind,
              static_cast<uint32_t>(Interception::Hooks::OpenGL::ClientArrayKind::TEX_COORD) );
    EXPECT_EQ(array_vec[1].pointer,
              reinterpret_cast<uint64_t>(data_u8vec48) );
    EXPECT_EQ(array_vec[2].kind,
              static_cast<uint32_t>(Interception::Hooks::OpenGL::ClientArrayKind::VERTEX) );
    EXPECT_EQ(array_vec[2].pointer,
              reinterpret_cast<uint64_t>(data_u8vec48 + 12) );
    EXPECT_EQ(array_vec[2].stride,
              24u);
}

TEST(ClientArrayManager, MapsArrayTokensToKinds)
{
    Interception::Hooks::OpenGL::ClientArrayKind kind;

    EXPECT_TRUE(Interception::Hooks::OpenGL::ClientArrayManager::get_kind_for_array_enum(GL_TEXTURE_COORD_ARRAY,
                                                                 &kind) );
    EXPECT_EQ(kind,
              Interception::Hooks::OpenGL::ClientArrayKind::TEX_COORD);
    EXPECT_FALSE(Interception::Hooks::OpenGL::ClientArrayManager::get_kind_for_array_enum(GL_LIGHTING,
                                                                  &kind) );
}

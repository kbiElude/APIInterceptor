/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of reading the structures stored for D3D8 calls.
 */
#include <gtest/gtest.h>
#include "interception/core/D3D8Utils/value_readers.h"
#include "d3d8_struct_bytes.h"
#include <vector>

TEST(D3D8ValueReaders, MatrixIsReadFromItsBytes)
{
    Interception::Hooks::D3D8::D3DMATRIX matrix = {};
    float                                source_fp32vec16[16];

    for (uint32_t n_element = 0;
                  n_element < 16;
                ++n_element)
    {
        source_fp32vec16[n_element] = static_cast<float>(n_element);
    }

    ASSERT_TRUE(Interception::Core::D3D8Utils::parse_matrix(reinterpret_cast<const uint8_t*>(source_fp32vec16),
                                                            sizeof(source_fp32vec16),
                                                           &matrix) );

    EXPECT_EQ(matrix.m[0][0],
              0.0f);
    EXPECT_EQ(matrix.m[1][2],
              6.0f);
    EXPECT_EQ(matrix.m[3][3],
              15.0f);
}

TEST(D3D8ValueReaders, MatrixOfAnotherSizeIsRejected)
{
    Interception::Hooks::D3D8::D3DMATRIX      matrix     = {};
    std::vector<uint8_t> bytes_u8_vec(sizeof(Interception::Hooks::D3D8::D3DMATRIX) - 1);

    matrix.m[0][0] = 5.0f;

    EXPECT_FALSE(Interception::Core::D3D8Utils::parse_matrix(bytes_u8_vec.data(),
                                                             bytes_u8_vec.size(),
                                                            &matrix) );
    EXPECT_EQ   (matrix.m[0][0],
                 5.0f);
}

TEST(D3D8ValueReaders, PresentParametersAreReadWhateverThePointerSize)
{
    const size_t pointer_n_bytes_array[] = {sizeof(uint32_t), sizeof(uint64_t)};

    for (const auto& pointer_n_bytes : pointer_n_bytes_array)
    {
        Interception::Core::D3D8Utils::PresentParameters parameters;
        const auto                                       bytes_u8_vec = Tests::D3D8StructBytes::build_present_parameters(pointer_n_bytes);

        ASSERT_TRUE(Interception::Core::D3D8Utils::parse_present_parameters(bytes_u8_vec.data(),
                                                                            bytes_u8_vec.size(),
                                                                           &parameters) ) << "pointer size " << pointer_n_bytes;

        EXPECT_EQ(parameters.back_buffer_width,
                  800u);
        EXPECT_EQ(parameters.back_buffer_height,
                  600u);
        EXPECT_EQ(parameters.back_buffer_format,
                  Interception::Hooks::D3D8::D3DFMT_X8R8G8B8);
        EXPECT_EQ(parameters.back_buffer_count,
                  2u);
        EXPECT_EQ(parameters.swap_effect,
                  Interception::Hooks::D3D8::D3DSWAPEFFECT_FLIP);
        EXPECT_FALSE(parameters.windowed);
        EXPECT_TRUE (parameters.enable_auto_depth_stencil);
        EXPECT_EQ   (parameters.auto_depth_stencil_format,
                     Interception::Hooks::D3D8::D3DFMT_D24S8);
        EXPECT_EQ   (parameters.flags,
                     0x10u);
        EXPECT_EQ   (parameters.full_screen_refresh_rate_in_hz,
                     60u);
        EXPECT_EQ   (parameters.full_screen_presentation_interval,
                     1u);
    }
}

TEST(D3D8ValueReaders, PresentParametersOfAnotherSizeAreRejected)
{
    Interception::Core::D3D8Utils::PresentParameters parameters;
    auto                                             bytes_u8_vec = Tests::D3D8StructBytes::build_present_parameters(sizeof(uint32_t) );

    parameters.back_buffer_width = 7;

    bytes_u8_vec.push_back(0);

    EXPECT_FALSE(Interception::Core::D3D8Utils::parse_present_parameters(bytes_u8_vec.data(),
                                                                         bytes_u8_vec.size(),
                                                                        &parameters) );
    EXPECT_EQ   (parameters.back_buffer_width,
                 7u);
}

TEST(D3D8ValueReaders, ViewportIsReadFromItsBytes)
{
    Interception::Hooks::D3D8::D3DVIEWPORT8 source   = {0, 45, 800, 510, 0.0f, 1.0f};
    Interception::Hooks::D3D8::D3DVIEWPORT8 viewport = {};

    ASSERT_TRUE(Interception::Core::D3D8Utils::parse_viewport(reinterpret_cast<const uint8_t*>(&source),
                                                              sizeof(source),
                                                             &viewport) );

    EXPECT_EQ(viewport.Y,
              45u);
    EXPECT_EQ(viewport.Width,
              800u);
    EXPECT_EQ(viewport.Height,
              510u);
    EXPECT_EQ(viewport.MaxZ,
              1.0f);
}

TEST(D3D8ValueReaders, ViewportOfAnotherSizeIsRejected)
{
    Interception::Hooks::D3D8::D3DVIEWPORT8   viewport  = {};
    std::vector<uint8_t> bytes_u8_vec(sizeof(Interception::Hooks::D3D8::D3DVIEWPORT8) + 1);

    EXPECT_FALSE(Interception::Core::D3D8Utils::parse_viewport(bytes_u8_vec.data(),
                                                               bytes_u8_vec.size(),
                                                              &viewport) );
}

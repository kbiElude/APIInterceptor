/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks that the structure of a strided draw is made again from what the dump holds: the structure for the distances between the vertices, and
 * the chunk of the arrays.
 */
#include <gtest/gtest.h>
#include "Interception/Core/D3D7Utils/strided_layout.h"
#include <string.h>
#include <vector>

namespace
{
    using Interception::Core::D3D7Utils::StridedLayout;
    using Interception::Hooks::D3D7::D3DDRAWPRIMITIVESTRIDEDDATA;

    /* The chunk, as the hook makes it: the number of the arrays, the size of each, and the arrays. */
    std::vector<uint8_t> make_chunk(const std::vector<std::vector<uint8_t> >& in_array_vec)
    {
        const uint32_t       n_arrays = StridedLayout::N_ARRAYS;
        std::vector<uint8_t> result_u8_vec(reinterpret_cast<const uint8_t*>(&n_arrays),
                                           reinterpret_cast<const uint8_t*>(&n_arrays) + sizeof(n_arrays) );

        for (size_t n_array = 0;
                    n_array < StridedLayout::N_ARRAYS;
                  ++n_array)
        {
            const uint32_t n_bytes = (n_array < in_array_vec.size() ) ? static_cast<uint32_t>(in_array_vec.at(n_array).size() )
                                                                      : 0;

            result_u8_vec.insert(result_u8_vec.end(),
                                 reinterpret_cast<const uint8_t*>(&n_bytes),
                                 reinterpret_cast<const uint8_t*>(&n_bytes) + sizeof(n_bytes) );
        }

        for (const auto& array_u8_vec : in_array_vec)
        {
            result_u8_vec.insert(result_u8_vec.end(),
                                 array_u8_vec.begin(),
                                 array_u8_vec.end  () );
        }

        return result_u8_vec;
    }
}

TEST(StridedLayout, TheArraysAreWhereTheChunkPutThemWithTheDistancesOfTheStructure)
{
    D3DDRAWPRIMITIVESTRIDEDDATA dumped = {};

    dumped.position.dwStride = 16;
    dumped.diffuse.dwStride  = 4;

    /* The position (3 vertices at a distance of 16, the last one not padded), then the diffuse colors. */
    const auto chunk_u8_vec = make_chunk({std::vector<uint8_t>(2 * 16 + 12, 0xAA),
                                          std::vector<uint8_t>(),
                                          std::vector<uint8_t>(3 * 4, 0xBB)});

    D3DDRAWPRIMITIVESTRIDEDDATA rebuilt = {};

    ASSERT_TRUE(StridedLayout::rebuild(reinterpret_cast<const uint8_t*>(&dumped),
                                       sizeof(dumped),
                                       chunk_u8_vec.data(),
                                       chunk_u8_vec.size(),
                                      &rebuilt) );

    const uint8_t* const base_ptr = chunk_u8_vec.data() + sizeof(uint32_t) * (1 + StridedLayout::N_ARRAYS);

    EXPECT_EQ(rebuilt.position.lpvData,
              base_ptr);
    EXPECT_EQ(rebuilt.position.dwStride,
              16u);
    EXPECT_EQ(rebuilt.normal.lpvData,
              nullptr);
    EXPECT_EQ(rebuilt.diffuse.lpvData,
              base_ptr + 2 * 16 + 12);
    EXPECT_EQ(rebuilt.diffuse.dwStride,
              4u);
    EXPECT_EQ(rebuilt.specular.lpvData,
              nullptr);
}

TEST(StridedLayout, ChunksOfTheWrongSizeAreRefused)
{
    D3DDRAWPRIMITIVESTRIDEDDATA dumped  = {};
    D3DDRAWPRIMITIVESTRIDEDDATA rebuilt = {};
    auto                        chunk_u8_vec = make_chunk({std::vector<uint8_t>(12, 0)});

    /* The structure is not one. */
    EXPECT_FALSE(StridedLayout::rebuild(reinterpret_cast<const uint8_t*>(&dumped),
                                        sizeof(dumped) - 1,
                                        chunk_u8_vec.data(),
                                        chunk_u8_vec.size(),
                                       &rebuilt) );

    /* The chunk ends before the array does. */
    chunk_u8_vec.resize(chunk_u8_vec.size() - 4);

    EXPECT_FALSE(StridedLayout::rebuild(reinterpret_cast<const uint8_t*>(&dumped),
                                        sizeof(dumped),
                                        chunk_u8_vec.data(),
                                        chunk_u8_vec.size(),
                                       &rebuilt) );

    /* There is no chunk. */
    EXPECT_FALSE(StridedLayout::rebuild(reinterpret_cast<const uint8_t*>(&dumped),
                                        sizeof(dumped),
                                        nullptr,
                                        0,
                                       &rebuilt) );
}

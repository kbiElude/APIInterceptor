/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the chunks which hold the strings passed to GL.
 */
#include <gtest/gtest.h>
#include "Common/callbacks.h"
#include "Interception/Hooks/OpenGL/string_array_chunk.h"
#include "Interception/Hooks/OpenGL/string_chunk.h"
#include <string.h>
#include <string>
#include <vector>

/* Returns the contents of a data chunk. */
static std::vector<uint8_t> get_chunk_contents(const APIInterceptor::DataChunkID& in_chunk_id)
{
    const void*          data_ptr   = nullptr;
    uint32_t             n_bytes    = 0;
    std::vector<uint8_t> result_u8_vec;

    if (APIInterceptor::get_data_chunk(in_chunk_id,
                                      &data_ptr,
                                      &n_bytes) )
    {
        result_u8_vec.assign(static_cast<const uint8_t*>(data_ptr),
                             static_cast<const uint8_t*>(data_ptr) + n_bytes);
    }

    return result_u8_vec;
}

/* The layout of a string array chunk, built the way the tests expect it to be. */
static std::vector<uint8_t> build_expected_array(const std::vector<std::string>& in_string_vec)
{
    const uint32_t       n_strings = static_cast<uint32_t>(in_string_vec.size() );
    std::vector<uint8_t> result_u8_vec;

    result_u8_vec.insert(result_u8_vec.end(),
                         reinterpret_cast<const uint8_t*>(&n_strings),
                         reinterpret_cast<const uint8_t*>(&n_strings) + sizeof(n_strings) );

    for (const auto& current_string : in_string_vec)
    {
        const uint32_t n_characters = static_cast<uint32_t>(current_string.size() );

        result_u8_vec.insert(result_u8_vec.end(),
                             reinterpret_cast<const uint8_t*>(&n_characters),
                             reinterpret_cast<const uint8_t*>(&n_characters) + sizeof(n_characters) );
        result_u8_vec.insert(result_u8_vec.end(),
                             current_string.begin(),
                             current_string.end  () );
    }

    return result_u8_vec;
}

TEST(StringArrayChunk, HonoursExplicitLengthsAndTerminators)
{
    const char* const strings_ptr_vec[] = {"abcdef", "ghi", nullptr};
    const int32_t     lengths_i32vec3[] = {3, -1, 5};

    OpenGL::StringArrayChunk chunk(strings_ptr_vec,
                                   3,
                                   lengths_i32vec3);

    /* A null string is stored as empty, whatever its length says. */
    EXPECT_EQ(get_chunk_contents(chunk.get_id() ),
              build_expected_array({"abc", "ghi", ""}) );
}

TEST(StringArrayChunk, IsEmptyWithoutStrings)
{
    const char* const strings_ptr_vec[] = {"a"};

    OpenGL::StringArrayChunk no_array_chunk(nullptr,
                                            1,
                                            nullptr);
    OpenGL::StringArrayChunk no_strings_chunk(strings_ptr_vec,
                                              0,
                                              nullptr);

    EXPECT_TRUE(get_chunk_contents(no_array_chunk.get_id() ).empty() );
    EXPECT_TRUE(get_chunk_contents(no_strings_chunk.get_id() ).empty() );
}

TEST(StringArrayChunk, NullLengthsMeanTerminatedStrings)
{
    const char* const strings_ptr_vec[] = {"vertex", "main"};

    OpenGL::StringArrayChunk chunk(strings_ptr_vec,
                                   2,
                                   nullptr);

    EXPECT_EQ(get_chunk_contents(chunk.get_id() ),
              build_expected_array({"vertex", "main"}) );
}

TEST(StringChunk, CopiesTheStringOnceAndOnlyWhenAsked)
{
    const auto n_chunks_before = APIInterceptor::get_n_data_chunks();

    OpenGL::StringChunk chunk("uColor");

    EXPECT_EQ(APIInterceptor::get_n_data_chunks(),
              n_chunks_before);

    const auto first_id  = chunk.get_id();
    const auto second_id = chunk.get_id();

    EXPECT_EQ(first_id,
              second_id);
    EXPECT_EQ(APIInterceptor::get_n_data_chunks(),
              n_chunks_before + 1);

    /* The terminator is stored, too. */
    EXPECT_EQ(get_chunk_contents(first_id),
              std::vector<uint8_t>({'u', 'C', 'o', 'l', 'o', 'r', 0}) );
}

TEST(StringChunk, NullStringGivesAnEmptyChunk)
{
    OpenGL::StringChunk chunk(nullptr);

    EXPECT_TRUE(get_chunk_contents(chunk.get_id() ).empty() );
}

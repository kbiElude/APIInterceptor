/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <gtest/gtest.h>
#include "APIDumpLoader/APIDumpLoader.h"
#include "workload_file_builder.h"
#include <stdio.h>

void Tests::WorkloadFileBuilder::append_bytes(std::vector<uint8_t>* inout_u8_vec_ptr,
                                              const void*           in_data_ptr,
                                              const size_t&         in_n_bytes)
{
    const uint8_t* data_u8_ptr = static_cast<const uint8_t*>(in_data_ptr);

    inout_u8_vec_ptr->insert(inout_u8_vec_ptr->end(),
                             data_u8_ptr,
                             data_u8_ptr + in_n_bytes);
}

/* A call with one input argument, no output arguments and no returned value. */
void Tests::WorkloadFileBuilder::append_call(std::vector<uint8_t>* inout_u8_vec_ptr,
                                             const uint32_t&       in_u32_argument)
{
    const auto     function          = APIInterceptor::APIFUNCTION_GL_GLACCUM;
    constexpr uint32_t N_IN_ARGUMENTS    = 1;
    constexpr uint32_t N_OUT_ARGUMENTS   = 0;
    const auto     no_value_argument = APIInterceptor::APIFunctionArgument();
    const auto     u32_argument      = APIInterceptor::APIFunctionArgument::create_u32(in_u32_argument);

    append_bytes(inout_u8_vec_ptr,
                &function,
                 sizeof(function) );
    append_bytes(inout_u8_vec_ptr,
                &N_IN_ARGUMENTS,
                 sizeof(N_IN_ARGUMENTS) );
    append_bytes(inout_u8_vec_ptr,
                &N_OUT_ARGUMENTS,
                 sizeof(N_OUT_ARGUMENTS) );

    u32_argument.serialize_to_u8_vec     (inout_u8_vec_ptr);
    no_value_argument.serialize_to_u8_vec(inout_u8_vec_ptr);
}

void Tests::WorkloadFileBuilder::append_chunk(std::vector<uint8_t>*       inout_u8_vec_ptr,
                                              const std::vector<uint8_t>& in_data_u8_vec)
{
    const uint32_t n_bytes = static_cast<uint32_t>(in_data_u8_vec.size() );

    append_bytes(inout_u8_vec_ptr,
                &n_bytes,
                 sizeof(n_bytes) );
    append_bytes(inout_u8_vec_ptr,
                 in_data_u8_vec.data(),
                 in_data_u8_vec.size() );
}

void Tests::WorkloadFileBuilder::append_header(std::vector<uint8_t>* inout_u8_vec_ptr,
                                               const uint32_t&       in_n_api_calls,
                                               const uint32_t&       in_n_data_chunks,
                                               const uint32_t&       in_n_surfaces)
{
    append_bytes(inout_u8_vec_ptr,
                &in_n_api_calls,
                 sizeof(uint32_t) );
    append_bytes(inout_u8_vec_ptr,
                &in_n_data_chunks,
                 sizeof(uint32_t) );
    append_bytes(inout_u8_vec_ptr,
                &in_n_surfaces,
                 sizeof(uint32_t) );
}

void Tests::WorkloadFileBuilder::append_surface(std::vector<uint8_t>*       inout_u8_vec_ptr,
                                                const std::vector<uint8_t>& in_data_u8_vec)
{
    const uint32_t extents_u32vec2[2] = {2, 1};
    const uint32_t n_bytes            = static_cast<uint32_t>(in_data_u8_vec.size() );

    append_bytes(inout_u8_vec_ptr,
                 extents_u32vec2,
                 sizeof(extents_u32vec2) );
    append_bytes(inout_u8_vec_ptr,
                &n_bytes,
                 sizeof(n_bytes) );
    append_bytes(inout_u8_vec_ptr,
                 in_data_u8_vec.data(),
                 in_data_u8_vec.size() );
}

size_t Tests::WorkloadFileBuilder::build_two_segments(std::vector<uint8_t>* out_u8_vec_ptr)
{
    size_t result = 0;

    append_header(out_u8_vec_ptr,
                  2,  /* in_n_api_calls   */
                  2,  /* in_n_data_chunks */
                  1); /* in_n_surfaces    */
    append_call  (out_u8_vec_ptr,
                  10);
    append_call  (out_u8_vec_ptr,
                  11);
    append_chunk (out_u8_vec_ptr,
                  {1, 2, 3});
    append_chunk (out_u8_vec_ptr,
                  {});
    append_surface(out_u8_vec_ptr,
                   {1, 2, 3, 4, 5, 6, 7, 8});

    append_header(out_u8_vec_ptr,
                  1,  /* in_n_api_calls   */
                  1,  /* in_n_data_chunks */
                  0); /* in_n_surfaces    */
    append_call  (out_u8_vec_ptr,
                  12);

    result = out_u8_vec_ptr->size();

    append_chunk(out_u8_vec_ptr,
                 {9, 9, 9, 9});

    return result;
}

const char* Tests::WorkloadFileBuilder::get_filename_ptr()
{
    static constexpr const char* FILENAME_PTR = "test_workload_reader.tmp";

    return FILENAME_PTR;
}

void Tests::WorkloadFileBuilder::write_file(const std::vector<uint8_t>& in_u8_vec)
{
    FILE* file_handle = ::fopen(get_filename_ptr(),
                                "wb");

    ASSERT_NE(file_handle,
              nullptr);

    ::fwrite(in_u8_vec.data(),
             in_u8_vec.size(),
             1,
             file_handle);
    ::fclose(file_handle);
}

/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <gtest/gtest.h>
#include "Capture/APIDumpLoader/api_dump_loader.h"
#include "Common/workload_format.h"
#include "workload_file_builder.h"
#include "zstd.h"
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

void Tests::WorkloadFileBuilder::append_call(std::vector<uint8_t>*              inout_u8_vec_ptr,
                                             const uint32_t&                    in_u32_argument,
                                             const APIInterceptor::APIFunction& in_function)
{
    append_call_with_argument(inout_u8_vec_ptr,
                              in_function,
                              APIInterceptor::APIFunctionArgument::create_u32(in_u32_argument),
                              in_u32_argument);
}

/* A call with one input argument, no output arguments and no returned value. The timestamp is TIMESTAMP_BASE plus the
 * offset.
 */
void Tests::WorkloadFileBuilder::append_call_with_argument(std::vector<uint8_t>*                      inout_u8_vec_ptr,
                                                           const APIInterceptor::APIFunction&         in_function,
                                                           const APIInterceptor::APIFunctionArgument& in_argument,
                                                           const uint32_t&                            in_timestamp_offset)
{
    constexpr uint32_t N_IN_ARGUMENTS    = 1;
    constexpr uint32_t N_OUT_ARGUMENTS   = 0;
    const auto         no_value_argument = APIInterceptor::APIFunctionArgument();

    /* Copies: the class constants have no out-of-class definition (pre-C++17), so they must not be bound to a reference. */
    const uint32_t thread_id = THREAD_ID;
    const uint64_t timestamp = TIMESTAMP_BASE + in_timestamp_offset;

    append_bytes(inout_u8_vec_ptr,
                &in_function,
                 sizeof(in_function) );
    append_bytes(inout_u8_vec_ptr,
                &N_IN_ARGUMENTS,
                 sizeof(N_IN_ARGUMENTS) );
    append_bytes(inout_u8_vec_ptr,
                &N_OUT_ARGUMENTS,
                 sizeof(N_OUT_ARGUMENTS) );
    append_bytes(inout_u8_vec_ptr,
                &thread_id,
                 sizeof(thread_id) );
    append_bytes(inout_u8_vec_ptr,
                &timestamp,
                 sizeof(timestamp) );

    in_argument.serialize_to_u8_vec      (inout_u8_vec_ptr);
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

void Tests::WorkloadFileBuilder::append_compressed_segment(std::vector<uint8_t>*       inout_u8_vec_ptr,
                                                           const std::vector<uint8_t>& in_segment_u8_vec)
{
    constexpr int COMPRESSION_LEVEL = 1;

    const size_t  file_n_bytes = inout_u8_vec_ptr->size();
    const size_t  max_n_bytes  = ::ZSTD_compressBound(in_segment_u8_vec.size() );
    size_t        n_bytes      = 0;

    inout_u8_vec_ptr->resize(file_n_bytes + max_n_bytes);

    n_bytes = ::ZSTD_compress(inout_u8_vec_ptr->data() + file_n_bytes,
                              max_n_bytes,
                              in_segment_u8_vec.data(),
                              in_segment_u8_vec.size(),
                              COMPRESSION_LEVEL);

    ASSERT_FALSE(::ZSTD_isError(n_bytes) );

    inout_u8_vec_ptr->resize(file_n_bytes + n_bytes);
}

void Tests::WorkloadFileBuilder::append_file_header(std::vector<uint8_t>* inout_u8_vec_ptr)
{
    APIInterceptor::WorkloadFormat::WorkloadFileHeader header = {};

    ::memcpy(header.magic_i8vec8,
             APIInterceptor::WorkloadFormat::MAGIC,
             sizeof(header.magic_i8vec8) );

    header.pointer_n_bytes = POINTER_N_BYTES;
    header.qpc_frequency   = QPC_FREQUENCY;
    header.version         = APIInterceptor::WorkloadFormat::FILE_VERSION;

    append_bytes(inout_u8_vec_ptr,
                &header,
                 sizeof(header) );
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

/* As the dumper writes a segment: the compressor is not told how large it is, so the frame does not say. */
void Tests::WorkloadFileBuilder::append_streamed_segment(std::vector<uint8_t>*       inout_u8_vec_ptr,
                                                         const std::vector<uint8_t>& in_segment_u8_vec)
{
    constexpr int COMPRESSION_LEVEL = 1;

    const size_t     file_n_bytes = inout_u8_vec_ptr->size();
    const size_t     max_n_bytes  = ::ZSTD_compressBound(in_segment_u8_vec.size() );
    ZSTD_CCtx* const compressor   = ::ZSTD_createCCtx();
    ZSTD_inBuffer    input        = {in_segment_u8_vec.data(), in_segment_u8_vec.size(), 0};
    size_t           n_remaining  = 0;

    ASSERT_NE(compressor,
              nullptr);

    inout_u8_vec_ptr->resize(file_n_bytes + max_n_bytes);

    ::ZSTD_CCtx_setParameter(compressor,
                             ZSTD_c_checksumFlag,
                             1);
    ::ZSTD_CCtx_setParameter(compressor,
                             ZSTD_c_compressionLevel,
                             COMPRESSION_LEVEL);

    ZSTD_outBuffer output = {inout_u8_vec_ptr->data() + file_n_bytes, max_n_bytes, 0};

    n_remaining = ::ZSTD_compressStream2(compressor,
                                        &output,
                                        &input,
                                         ZSTD_e_end);

    ASSERT_FALSE(::ZSTD_isError(n_remaining) );
    ASSERT_EQ   (n_remaining,
                 0u);

    inout_u8_vec_ptr->resize(file_n_bytes + output.pos);

    ::ZSTD_freeCCtx(compressor);
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

void Tests::WorkloadFileBuilder::build_chunk_references(std::vector<uint8_t>* out_u8_vec_ptr)
{
    constexpr uint32_t N_FRAMES = 3;

    std::vector<uint8_t> segment_u8_vec;

    append_file_header(out_u8_vec_ptr);
    append_header     (&segment_u8_vec,
                       N_FRAMES * 2 + 1, /* a call and a SwapBuffers call for each frame, and the second reference of frame 1 */
                       4,                /* in_n_data_chunks */
                       0);               /* in_n_surfaces    */

    for (uint32_t n_frame = 0;
                  n_frame < N_FRAMES;
                ++n_frame)
    {
        append_call_with_argument(&segment_u8_vec,
                                  APIInterceptor::APIFUNCTION_GL_GLACCUM,
                                  APIInterceptor::APIFunctionArgument::create_data_chunk_id(n_frame),
                                  n_frame);

        if (n_frame == 1)
        {
            append_call_with_argument(&segment_u8_vec,
                                      APIInterceptor::APIFUNCTION_GL_GLACCUM,
                                      APIInterceptor::APIFunctionArgument::create_data_chunk_id(0),
                                      n_frame);
        }

        append_call_with_argument(&segment_u8_vec,
                                  APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS,
                                  APIInterceptor::APIFunctionArgument::create_void_ptr(nullptr),
                                  n_frame);
    }

    for (uint32_t n_chunk = 0;
                  n_chunk < 4;
                ++n_chunk)
    {
        append_chunk(&segment_u8_vec,
                     std::vector<uint8_t>(n_chunk + 1,
                                          static_cast<uint8_t>(n_chunk + 1) ) );
    }

    append_compressed_segment(out_u8_vec_ptr,
                              segment_u8_vec);
}

void Tests::WorkloadFileBuilder::build_file_without_header(std::vector<uint8_t>* out_u8_vec_ptr)
{
    append_header(out_u8_vec_ptr,
                  1,  /* in_n_api_calls   */
                  0,  /* in_n_data_chunks */
                  0); /* in_n_surfaces    */
    append_call  (out_u8_vec_ptr,
                  10);
}

void Tests::WorkloadFileBuilder::build_frames(std::vector<uint8_t>* out_u8_vec_ptr,
                                              const uint32_t&       in_n_frames,
                                              const uint32_t&       in_n_calls_per_frame)
{
    std::vector<uint8_t> segment_u8_vec;

    append_file_header(out_u8_vec_ptr);
    append_header     (&segment_u8_vec,
                       in_n_frames * (in_n_calls_per_frame + 1),
                       0,  /* in_n_data_chunks */
                       0); /* in_n_surfaces    */

    for (uint32_t n_frame = 0;
                  n_frame < in_n_frames;
                ++n_frame)
    {
        for (uint32_t n_call = 0;
                      n_call < in_n_calls_per_frame;
                    ++n_call)
        {
            /* A call which the replay has nothing to do with. */
            append_call(&segment_u8_vec,
                        n_frame * in_n_calls_per_frame + n_call,
                        APIInterceptor::APIFUNCTION_GDI32_GETPIXELFORMAT);
        }

        /* No window: the frame ends, whatever the replay is able to present. */
        append_call_with_argument(&segment_u8_vec,
                                  APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS,
                                  APIInterceptor::APIFunctionArgument::create_void_ptr(nullptr),
                                  n_frame);
    }

    append_compressed_segment(out_u8_vec_ptr,
                              segment_u8_vec);
}

void Tests::WorkloadFileBuilder::build_large_chunk(std::vector<uint8_t>* out_u8_vec_ptr)
{
    std::vector<uint8_t> chunk_u8_vec(LARGE_CHUNK_N_BYTES);
    std::vector<uint8_t> segment_u8_vec;

    for (size_t n_byte = 0;
                n_byte < chunk_u8_vec.size();
              ++n_byte)
    {
        chunk_u8_vec.at(n_byte) = get_large_chunk_byte(n_byte);
    }

    append_file_header(out_u8_vec_ptr);

    append_header(&segment_u8_vec,
                  1,  /* in_n_api_calls   */
                  1,  /* in_n_data_chunks */
                  0); /* in_n_surfaces    */
    append_call  (&segment_u8_vec,
                  10);
    append_chunk (&segment_u8_vec,
                  chunk_u8_vec);

    append_compressed_segment(out_u8_vec_ptr,
                              segment_u8_vec);
}

void Tests::WorkloadFileBuilder::build_many_segments(std::vector<uint8_t>* out_u8_vec_ptr,
                                                     const uint32_t&       in_n_segments,
                                                     const uint32_t&       in_n_calls_per_segment,
                                                     const size_t&         in_n_bytes_per_chunk)
{
    constexpr uint32_t N_CALL_ARGUMENTS_PER_SEGMENT = 1000; /* the argument of a call is S * this + N */

    append_file_header(out_u8_vec_ptr);

    for (uint32_t n_segment = 0;
                  n_segment < in_n_segments;
                ++n_segment)
    {
        std::vector<uint8_t> segment_u8_vec;

        append_header(&segment_u8_vec,
                      in_n_calls_per_segment,
                      N_CHUNKS_PER_SEGMENT,
                      0); /* in_n_surfaces */

        for (uint32_t n_call = 0;
                      n_call < in_n_calls_per_segment;
                    ++n_call)
        {
            append_call(&segment_u8_vec,
                        n_segment * N_CALL_ARGUMENTS_PER_SEGMENT + n_call);
        }

        for (uint32_t n_chunk = 0;
                      n_chunk < N_CHUNKS_PER_SEGMENT;
                    ++n_chunk)
        {
            std::vector<uint8_t> chunk_u8_vec(in_n_bytes_per_chunk);

            for (size_t n_byte = 0;
                        n_byte < in_n_bytes_per_chunk;
                      ++n_byte)
            {
                chunk_u8_vec.at(n_byte) = get_segment_chunk_byte(n_segment,
                                                                 n_chunk,
                                                                 n_byte);
            }

            append_chunk(&segment_u8_vec,
                         chunk_u8_vec);
        }

        append_streamed_segment(out_u8_vec_ptr,
                                segment_u8_vec);
    }
}

void Tests::WorkloadFileBuilder::build_segments(std::vector<uint8_t>* out_u8_vec_ptr,
                                                const uint32_t&       in_n_segments,
                                                const uint32_t&       in_n_calls_per_segment,
                                                const uint32_t&       in_n_calls_per_frame)
{
    uint64_t n_call_in_file = 0;

    append_file_header(out_u8_vec_ptr);

    for (uint32_t n_segment = 0;
                  n_segment < in_n_segments;
                ++n_segment)
    {
        std::vector<uint8_t> segment_u8_vec;

        append_header(&segment_u8_vec,
                      in_n_calls_per_segment,
                      1,  /* in_n_data_chunks */
                      0); /* in_n_surfaces    */

        for (uint32_t n_call = 0;
                      n_call < in_n_calls_per_segment;
                    ++n_call, ++n_call_in_file)
        {
            if ( (n_call_in_file + 1) % (in_n_calls_per_frame + 1) == 0)
            {
                append_call_with_argument(&segment_u8_vec,
                                          APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS,
                                          APIInterceptor::APIFunctionArgument::create_void_ptr(nullptr),
                                          static_cast<uint32_t>(n_call_in_file) );
            }
            else
            {
                append_call(&segment_u8_vec,
                            static_cast<uint32_t>(n_call_in_file),
                            APIInterceptor::APIFUNCTION_GDI32_GETPIXELFORMAT);
            }
        }

        append_chunk(&segment_u8_vec,
                     std::vector<uint8_t>(4,
                                          static_cast<uint8_t>(n_segment) ) );

        append_compressed_segment(out_u8_vec_ptr,
                                  segment_u8_vec);
    }
}

void Tests::WorkloadFileBuilder::build_two_segments(std::vector<uint8_t>* out_u8_vec_ptr,
                                                    const size_t&         in_n_bytes_to_drop_from_second_segment)
{
    std::vector<uint8_t> first_segment_u8_vec;
    std::vector<uint8_t> second_segment_u8_vec;

    append_file_header(out_u8_vec_ptr);

    append_header(&first_segment_u8_vec,
                  2,  /* in_n_api_calls   */
                  2,  /* in_n_data_chunks */
                  1); /* in_n_surfaces    */
    append_call  (&first_segment_u8_vec,
                  10);
    append_call  (&first_segment_u8_vec,
                  11);
    append_chunk (&first_segment_u8_vec,
                  {1, 2, 3});
    append_chunk (&first_segment_u8_vec,
                  {});
    append_surface(&first_segment_u8_vec,
                   {1, 2, 3, 4, 5, 6, 7, 8});

    append_header(&second_segment_u8_vec,
                  1,  /* in_n_api_calls   */
                  1,  /* in_n_data_chunks */
                  0); /* in_n_surfaces    */
    append_call  (&second_segment_u8_vec,
                  12);
    append_chunk (&second_segment_u8_vec,
                  {9, 9, 9, 9});

    second_segment_u8_vec.resize(second_segment_u8_vec.size() - in_n_bytes_to_drop_from_second_segment);

    append_compressed_segment(out_u8_vec_ptr,
                              first_segment_u8_vec);
    append_compressed_segment(out_u8_vec_ptr,
                              second_segment_u8_vec);
}

const char* Tests::WorkloadFileBuilder::get_filename_ptr()
{
    static constexpr const char* FILENAME_PTR = "test_workload_reader.tmp";

    return FILENAME_PTR;
}

/* Not much of a pattern for the compressor to find, so that the segment spans many blocks. */
uint8_t Tests::WorkloadFileBuilder::get_large_chunk_byte(const size_t& in_n_byte)
{
    constexpr uint32_t MULTIPLIER = 2654435761u;
    constexpr uint32_t SHIFT      = 24;

    return static_cast<uint8_t>((in_n_byte * MULTIPLIER) >> SHIFT);
}

/* Runs of one value, so that the chunks compress far better than anything the reader would guess. */
uint8_t Tests::WorkloadFileBuilder::get_segment_chunk_byte(const uint32_t& in_n_segment,
                                                           const uint32_t& in_n_chunk,
                                                           const size_t&   in_n_byte)
{
    constexpr size_t RUN_N_BYTES = 64 * 1024;

    return static_cast<uint8_t>(in_n_segment * 7 + in_n_chunk * 3 + in_n_byte / RUN_N_BYTES);
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

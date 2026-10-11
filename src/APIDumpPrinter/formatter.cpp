/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "formatter.h"
#include "api_info.h"
#include "OpenGLUtils/utils_enum.h"
#include <assert.h>
#include <algorithm>
#include <vector>

bool APIDumpPrinter::are_arguments_identical(const APIInterceptor::APIFunctionArgument& in_argument_a,
                                             const APIInterceptor::APIFunctionArgument& in_argument_b,
                                             const APIDumpLoader::Workload&             in_workload)
{
    std::vector<uint8_t> a_u8_vec;
    std::vector<uint8_t> b_u8_vec;
    bool                 result = false;

    if (in_argument_a.type == in_argument_b.type)
    {
        if (in_argument_a.type == APIInterceptor::ARGTYPE_DATA_CHUNK_ID)
        {
            /* Chunks are identical if their contents are. */
            const auto chunk_id_a = in_argument_a.get_data_chunk_id();
            const auto chunk_id_b = in_argument_b.get_data_chunk_id();

            const auto chunk_a_ptr = APIDumpLoader::get_data_chunk_ptr(in_workload,
                                                                       chunk_id_a);
            const auto chunk_b_ptr = APIDumpLoader::get_data_chunk_ptr(in_workload,
                                                                       chunk_id_b);

            if (chunk_a_ptr != nullptr &&
                chunk_b_ptr != nullptr)
            {
                result = (*chunk_a_ptr == *chunk_b_ptr);
            }
        }
        else
        {
            in_argument_a.serialize_to_u8_vec(&a_u8_vec);
            in_argument_b.serialize_to_u8_vec(&b_u8_vec);

            result = (a_u8_vec == b_u8_vec);
        }
    }

    return result;
}

void APIDumpPrinter::print_argument(FILE*                                      in_file_handle,
                                    const APIInterceptor::APIFunctionArgument& in_argument,
                                    const APIDumpLoader::Workload&             in_workload)
{
    switch (in_argument.type)
    {
        case APIInterceptor::ARGTYPE_F32:
        {
            fprintf(in_file_handle,
                    "%f",
                    in_argument.get_fp32() );

            break;
        }

        case APIInterceptor::ARGTYPE_F64:
        {
            fprintf(in_file_handle,
                    "%lf",
                    in_argument.get_fp64() );

            break;
        }

        case APIInterceptor::ARGTYPE_I8:
        {
            fprintf(in_file_handle,
                    "%d",
                    static_cast<int32_t>(in_argument.get_i8() ));

            break;
        }

        case APIInterceptor::ARGTYPE_I16:
        {
            fprintf(in_file_handle,
                    "%d",
                    static_cast<int32_t>(in_argument.get_i16() ));

            break;
        }

        case APIInterceptor::ARGTYPE_I32:
        {
            fprintf(in_file_handle,
                    "%d",
                    in_argument.get_i32() );

            break;
        }

        case APIInterceptor::ARGTYPE_I64:
        {
            fprintf(in_file_handle,
                    "%lld",
                    static_cast<long long>(in_argument.get_i64() ));

            break;
        }

        case APIInterceptor::ARGTYPE_U8:
        {
            fprintf(in_file_handle,
                    "%u",
                    static_cast<uint32_t>(in_argument.get_u8() ));

            break;
        }

        case APIInterceptor::ARGTYPE_U16:
        {
            fprintf(in_file_handle,
                    "%u",
                    static_cast<uint32_t>(in_argument.get_u16() ));

            break;
        }

        case APIInterceptor::ARGTYPE_U32:
        {
            fprintf(in_file_handle,
                    "%u",
                    in_argument.get_u32() );

            break;
        }

        case APIInterceptor::ARGTYPE_U64:
        {
            fprintf(in_file_handle,
                    "%llu",
                    static_cast<unsigned long long>(in_argument.get_u64() ));

            break;
        }

        /* Pointer-typed arguments: the pointee was not captured, only the address is known. */
        case APIInterceptor::ARGTYPE_F32_PTR:
        {
            print_ptr(in_file_handle,
                      "f32*",
                      in_argument.get_fp32_ptr() );

            break;
        }

        case APIInterceptor::ARGTYPE_F64_PTR:
        {
            print_ptr(in_file_handle,
                      "f64*",
                      in_argument.get_fp64_ptr() );

            break;
        }

        case APIInterceptor::ARGTYPE_I8_PTR:
        {
            print_ptr(in_file_handle,
                      "i8*",
                      in_argument.get_i8_ptr() );

            break;
        }

        case APIInterceptor::ARGTYPE_I16_PTR:
        {
            print_ptr(in_file_handle,
                      "i16*",
                      in_argument.get_i16_ptr() );

            break;
        }

        case APIInterceptor::ARGTYPE_I32_PTR:
        {
            print_ptr(in_file_handle,
                      "i32*",
                      in_argument.get_i32_ptr() );

            break;
        }

        case APIInterceptor::ARGTYPE_U8_PTR:
        {
            print_ptr(in_file_handle,
                      "u8*",
                      in_argument.get_u8_ptr() );

            break;
        }

        case APIInterceptor::ARGTYPE_U16_PTR:
        {
            print_ptr(in_file_handle,
                      "u16*",
                      in_argument.get_u16_ptr() );

            break;
        }

        case APIInterceptor::ARGTYPE_U32_PTR:
        {
            print_ptr(in_file_handle,
                      "u32*",
                      in_argument.get_u32_ptr() );

            break;
        }

        case APIInterceptor::ARGTYPE_VOID_PTR:
        {
            print_ptr(in_file_handle,
                      "",
                      in_argument.get_ptr() );

            break;
        }

        case APIInterceptor::ARGTYPE_DATA_CHUNK_ID:
        {
            const auto chunk_id  = in_argument.get_data_chunk_id();
            const auto chunk_ptr = APIDumpLoader::get_data_chunk_ptr(in_workload,
                                                                     chunk_id);

            if (chunk_ptr != nullptr)
            {
                fprintf(in_file_handle,
                        "[data chunk %u, %u bytes]",
                        chunk_id,
                        static_cast<uint32_t>(chunk_ptr->size() ));
            }
            else
            {
                fprintf(in_file_handle,
                        "[data chunk %u (missing)]",
                        chunk_id);
            }

            break;
        }

        case APIInterceptor::ARGTYPE_I32_GLENUM:
        {
            fprintf(in_file_handle,
                    "%s",
                    OpenGL::Utils::get_raw_string_for_gl_enum(static_cast<GLenum>(in_argument.get_i32_glenum() )) );

            break;
        }

        case APIInterceptor::ARGTYPE_U32_GLENUM:
        {
            fprintf(in_file_handle,
                    "%s",
                    OpenGL::Utils::get_raw_string_for_gl_enum(in_argument.get_u32_glenum() ) );

            break;
        }

        default:
        {
            assert(false);

            fprintf(in_file_handle,
                    "<unknown arg type %d>",
                    static_cast<int>(in_argument.type) );

            break;
        }
    }
}

void APIDumpPrinter::print_call(FILE*                                  in_file_handle,
                                const APIDumpLoader::DumpedAPICall&    in_call,
                                const APIDumpLoader::Workload&         in_workload,
                                uint32_t                               in_n_hexdump_bytes,
                                std::set<APIInterceptor::DataChunkID>* inout_referenced_chunk_set_ptr,
                                D3D8Decoder*                           inout_d3d8_decoder_ptr)
{
    std::vector<APIInterceptor::DataChunkID> call_chunk_id_vec;
    const bool                               is_d3d8_call = (inout_d3d8_decoder_ptr != nullptr                   &&
                                                             get_api_group(in_call.func) == APIGroup::D3D8);

    /* D3D8 arguments are decoded by the decoder, if it knows them. */
    const auto print_call_argument_func = [&](const uint32_t&                            in_n_argument,
                                              const bool&                                in_is_out,
                                              const APIInterceptor::APIFunctionArgument& in_argument)
    {
        bool is_printed = false;

        if (is_d3d8_call)
        {
            is_printed = inout_d3d8_decoder_ptr->print_argument(in_file_handle,
                                                                in_call,
                                                                in_n_argument,
                                                                in_is_out,
                                                                in_argument,
                                                                in_workload);
        }

        if (is_printed == false)
        {
            print_argument(in_file_handle,
                           in_argument,
                           in_workload);
        }
    };

    auto collect_chunk_ids_func = [&](const std::vector<APIInterceptor::APIFunctionArgument>& in_argument_vec)
    {
        for (const auto& current_argument : in_argument_vec)
        {
            if (current_argument.type == APIInterceptor::ARGTYPE_DATA_CHUNK_ID)
            {
                const auto chunk_id = current_argument.get_data_chunk_id();

                /* The same chunk is typically reported in both pre- and post-call args. */
                if (std::find(call_chunk_id_vec.begin(),
                              call_chunk_id_vec.end  (),
                              chunk_id) == call_chunk_id_vec.end() )
                {
                    call_chunk_id_vec.push_back(chunk_id);
                }
            }
        }
    };

    fprintf(in_file_handle,
            "%s(",
            get_function_name(in_call.func) );

    for (size_t n_argument = 0; n_argument < in_call.arg_in_vec.size(); ++n_argument)
    {
        if (n_argument != 0)
        {
            fprintf(in_file_handle,
                    ", ");
        }

        print_call_argument_func(static_cast<uint32_t>(n_argument),
                                 false, /* in_is_out */
                                 in_call.arg_in_vec.at(n_argument) );
    }

    fprintf(in_file_handle,
            ")");

    /* Out args: only those updated by reference (value differs from the input), tagged with the arg index. */
    {
        bool is_first_out_argument = true;

        for (size_t n_argument = 0; n_argument < in_call.arg_out_vec.size(); ++n_argument)
        {
            const auto& out_argument = in_call.arg_out_vec.at(n_argument);
            bool        is_unchanged = false;

            if (n_argument < in_call.arg_in_vec.size() )
            {
                is_unchanged = are_arguments_identical(in_call.arg_in_vec.at(n_argument),
                                                       out_argument,
                                                       in_workload);
            }

            if (is_unchanged)
            {
                continue;
            }

            fprintf(in_file_handle,
                    "%s",
                    is_first_out_argument ? " [out: "
                                          : ", ");
            fprintf(in_file_handle,
                    "arg%u=",
                    static_cast<uint32_t>(n_argument) );

            print_call_argument_func(static_cast<uint32_t>(n_argument),
                                     true,  /* in_is_out */
                                     out_argument);

            is_first_out_argument = false;
        }

        if (!is_first_out_argument)
        {
            fprintf(in_file_handle,
                    "]");
        }
    }

    if (in_call.returned_value_ptr       != nullptr &&
        in_call.returned_value_ptr->type != APIInterceptor::UNKNOWN)
    {
        bool is_printed = false;

        fprintf(in_file_handle,
                " returned ");

        if (is_d3d8_call)
        {
            is_printed = inout_d3d8_decoder_ptr->print_returned_value(in_file_handle,
                                                                      in_call,
                                                                     *in_call.returned_value_ptr);
        }

        if (is_printed == false)
        {
            print_argument(in_file_handle,
                          *in_call.returned_value_ptr,
                           in_workload);
        }
    }

    fprintf(in_file_handle,
            "\n");

    collect_chunk_ids_func(in_call.arg_in_vec);
    collect_chunk_ids_func(in_call.arg_out_vec);

    for (const auto& chunk_id : call_chunk_id_vec)
    {
        if (inout_referenced_chunk_set_ptr != nullptr)
        {
            inout_referenced_chunk_set_ptr->insert(chunk_id);
        }

        const auto chunk_ptr = APIDumpLoader::get_data_chunk_ptr(in_workload,
                                                                 chunk_id);

        if (in_n_hexdump_bytes != 0       &&
            chunk_ptr          != nullptr)
        {
            fprintf(in_file_handle,
                    "    chunk %u:\n",
                    chunk_id);

            print_hexdump(in_file_handle,
                         *chunk_ptr,
                          in_n_hexdump_bytes);
        }
    }
}

void APIDumpPrinter::print_hexdump(FILE*                       in_file_handle,
                                   const std::vector<uint8_t>& in_chunk_u8_vec,
                                   uint32_t                    in_n_bytes_max)
{
    const uint32_t n_bytes_to_print = std::min<uint32_t>(in_n_bytes_max,
                                                         static_cast<uint32_t>(in_chunk_u8_vec.size() ));

    for (uint32_t offset = 0;
                  offset < n_bytes_to_print;
                  offset += 16)
    {
        fprintf(in_file_handle,
                "      +%06x ",
                offset);

        for (uint32_t n_column = 0; n_column < 16; ++n_column)
        {
            if (offset + n_column < n_bytes_to_print)
            {
                fprintf(in_file_handle,
                        " %02x",
                        in_chunk_u8_vec.at(offset + n_column) );
            }
            else
            {
                fprintf(in_file_handle,
                        "   ");
            }
        }

        fprintf(in_file_handle,
                "  |");

        for (uint32_t n_column = 0; n_column < 16 && offset + n_column < n_bytes_to_print; ++n_column)
        {
            const uint8_t character = in_chunk_u8_vec.at(offset + n_column);

            fprintf(in_file_handle,
                    "%c",
                    (character >= 32 && character < 127) ? character
                                                         : '.');
        }

        fprintf(in_file_handle,
                "|\n");
    }

    if (n_bytes_to_print < in_chunk_u8_vec.size() )
    {
        fprintf(in_file_handle,
                "      ... (%u more bytes)\n",
                static_cast<uint32_t>(in_chunk_u8_vec.size() ) - n_bytes_to_print);
    }
}

void APIDumpPrinter::print_ptr(FILE*       in_file_handle,
                               const char* in_type_prefix_ptr,
                               const void* in_ptr)
{
    if (in_ptr == nullptr)
    {
        fprintf(in_file_handle,
                "%sNULL",
                in_type_prefix_ptr);
    }
    else
    {
        fprintf(in_file_handle,
                "%s0x%llx",
                in_type_prefix_ptr,
                static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(in_ptr) ));
    }
}

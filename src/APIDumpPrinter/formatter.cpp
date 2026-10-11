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

bool APIDumpPrinter::are_arguments_identical(const APIInterceptor::APIFunctionArgument& in_arg_a,
                                             const APIInterceptor::APIFunctionArgument& in_arg_b)
{
    std::vector<uint8_t> a_u8_vec;
    std::vector<uint8_t> b_u8_vec;
    bool                 result = false;

    if (in_arg_a.type == in_arg_b.type)
    {
        in_arg_a.serialize_to_u8_vec(&a_u8_vec);
        in_arg_b.serialize_to_u8_vec(&b_u8_vec);

        result = (a_u8_vec == b_u8_vec);
    }

    return result;
}

void APIDumpPrinter::print_argument(FILE*                                      in_file_handle,
                                    const APIInterceptor::APIFunctionArgument& in_arg,
                                    const APIDumpLoader::Workload&             in_workload)
{
    switch (in_arg.type)
    {
        case APIInterceptor::ARGTYPE_F32:
        {
            fprintf(in_file_handle,
                    "%f",
                    in_arg.get_fp32() );

            break;
        }

        case APIInterceptor::ARGTYPE_F64:
        {
            fprintf(in_file_handle,
                    "%lf",
                    in_arg.get_fp64() );

            break;
        }

        case APIInterceptor::ARGTYPE_I8:
        {
            fprintf(in_file_handle,
                    "%d",
                    static_cast<int32_t>(in_arg.get_i8() ));

            break;
        }

        case APIInterceptor::ARGTYPE_I16:
        {
            fprintf(in_file_handle,
                    "%d",
                    static_cast<int32_t>(in_arg.get_i16() ));

            break;
        }

        case APIInterceptor::ARGTYPE_I32:
        {
            fprintf(in_file_handle,
                    "%d",
                    in_arg.get_i32() );

            break;
        }

        case APIInterceptor::ARGTYPE_I64:
        {
            fprintf(in_file_handle,
                    "%lld",
                    static_cast<long long>(in_arg.get_i64() ));

            break;
        }

        case APIInterceptor::ARGTYPE_U8:
        {
            fprintf(in_file_handle,
                    "%u",
                    static_cast<uint32_t>(in_arg.get_u8() ));

            break;
        }

        case APIInterceptor::ARGTYPE_U16:
        {
            fprintf(in_file_handle,
                    "%u",
                    static_cast<uint32_t>(in_arg.get_u16() ));

            break;
        }

        case APIInterceptor::ARGTYPE_U32:
        {
            fprintf(in_file_handle,
                    "%u",
                    in_arg.get_u32() );

            break;
        }

        case APIInterceptor::ARGTYPE_U64:
        {
            fprintf(in_file_handle,
                    "%llu",
                    static_cast<unsigned long long>(in_arg.get_u64() ));

            break;
        }

        /* Pointer-typed arguments: the pointee was not captured, only the address is known. */
        case APIInterceptor::ARGTYPE_F32_PTR:
        {
            print_ptr(in_file_handle,
                      "f32*",
                      in_arg.get_fp32_ptr() );

            break;
        }

        case APIInterceptor::ARGTYPE_F64_PTR:
        {
            print_ptr(in_file_handle,
                      "f64*",
                      in_arg.get_fp64_ptr() );

            break;
        }

        case APIInterceptor::ARGTYPE_I8_PTR:
        {
            print_ptr(in_file_handle,
                      "i8*",
                      in_arg.get_i8_ptr() );

            break;
        }

        case APIInterceptor::ARGTYPE_I16_PTR:
        {
            print_ptr(in_file_handle,
                      "i16*",
                      in_arg.get_i16_ptr() );

            break;
        }

        case APIInterceptor::ARGTYPE_I32_PTR:
        {
            print_ptr(in_file_handle,
                      "i32*",
                      in_arg.get_i32_ptr() );

            break;
        }

        case APIInterceptor::ARGTYPE_U8_PTR:
        {
            print_ptr(in_file_handle,
                      "u8*",
                      in_arg.get_u8_ptr() );

            break;
        }

        case APIInterceptor::ARGTYPE_U16_PTR:
        {
            print_ptr(in_file_handle,
                      "u16*",
                      in_arg.get_u16_ptr() );

            break;
        }

        case APIInterceptor::ARGTYPE_U32_PTR:
        {
            print_ptr(in_file_handle,
                      "u32*",
                      in_arg.get_u32_ptr() );

            break;
        }

        case APIInterceptor::ARGTYPE_VOID_PTR:
        {
            print_ptr(in_file_handle,
                      "",
                      in_arg.get_ptr() );

            break;
        }

        case APIInterceptor::ARGTYPE_DATA_CHUNK_ID:
        {
            const auto chunk_id = in_arg.get_data_chunk_id();

            if (chunk_id < in_workload.data_chunk_ptr_vec.size() )
            {
                fprintf(in_file_handle,
                        "[data chunk %u, %u bytes]",
                        chunk_id,
                        static_cast<uint32_t>(in_workload.data_chunk_ptr_vec.at(chunk_id)->size() ));
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
                    OpenGL::Utils::get_raw_string_for_gl_enum(static_cast<GLenum>(in_arg.get_i32_glenum() )) );

            break;
        }

        case APIInterceptor::ARGTYPE_U32_GLENUM:
        {
            fprintf(in_file_handle,
                    "%s",
                    OpenGL::Utils::get_raw_string_for_gl_enum(in_arg.get_u32_glenum() ) );

            break;
        }

        default:
        {
            assert(false);

            fprintf(in_file_handle,
                    "<unknown arg type %d>",
                    static_cast<int>(in_arg.type) );

            break;
        }
    }
}

void APIDumpPrinter::print_call(FILE*                                  in_file_handle,
                                const APIDumpLoader::DumpedAPICall&    in_call,
                                const APIDumpLoader::Workload&         in_workload,
                                uint32_t                               in_n_hexdump_bytes,
                                std::set<APIInterceptor::DataChunkID>* inout_referenced_chunks_ptr)
{
    std::vector<APIInterceptor::DataChunkID> call_chunk_id_vec;

    auto collect_chunk_ids_func = [&](const std::vector<APIInterceptor::APIFunctionArgument>& in_arg_vec)
    {
        for (const auto& current_arg : in_arg_vec)
        {
            if (current_arg.type == APIInterceptor::ARGTYPE_DATA_CHUNK_ID)
            {
                const auto chunk_id = current_arg.get_data_chunk_id();

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

    for (size_t n_arg = 0; n_arg < in_call.arg_in_vec.size(); ++n_arg)
    {
        if (n_arg != 0)
        {
            fprintf(in_file_handle,
                    ", ");
        }

        print_argument(in_file_handle,
                       in_call.arg_in_vec.at(n_arg),
                       in_workload);
    }

    fprintf(in_file_handle,
            ")");

    /* Entrypoints report all of their arguments again after the call, but only the ones the implementation updated
     * by reference (e.g. IDs written by glGenTextures) carry new information. Print those, tagged with the index
     * of the argument they belong to. Args which merely repeat the input are not output args.
     */
    {
        bool is_first_out_arg = true;

        for (size_t n_arg = 0; n_arg < in_call.arg_out_vec.size(); ++n_arg)
        {
            const auto& out_arg = in_call.arg_out_vec.at(n_arg);

            if (n_arg < in_call.arg_in_vec.size() &&
                are_arguments_identical(in_call.arg_in_vec.at(n_arg),
                                        out_arg) )
            {
                continue;
            }

            fprintf(in_file_handle,
                    "%s",
                    is_first_out_arg ? " [out: "
                                     : ", ");
            fprintf(in_file_handle,
                    "arg%u=",
                    static_cast<uint32_t>(n_arg) );

            print_argument(in_file_handle,
                           out_arg,
                           in_workload);

            is_first_out_arg = false;
        }

        if (!is_first_out_arg)
        {
            fprintf(in_file_handle,
                    "]");
        }
    }

    if (in_call.returned_value_ptr       != nullptr &&
        in_call.returned_value_ptr->type != APIInterceptor::UNKNOWN)
    {
        fprintf(in_file_handle,
                " returned ");

        print_argument(in_file_handle,
                      *in_call.returned_value_ptr,
                       in_workload);
    }

    fprintf(in_file_handle,
            "\n");

    collect_chunk_ids_func(in_call.arg_in_vec);
    collect_chunk_ids_func(in_call.arg_out_vec);

    for (const auto& chunk_id : call_chunk_id_vec)
    {
        if (inout_referenced_chunks_ptr != nullptr)
        {
            inout_referenced_chunks_ptr->insert(chunk_id);
        }

        if (in_n_hexdump_bytes != 0                                 &&
            chunk_id           <  in_workload.data_chunk_ptr_vec.size() )
        {
            fprintf(in_file_handle,
                    "    chunk %u:\n",
                    chunk_id);

            print_hexdump(in_file_handle,
                         *in_workload.data_chunk_ptr_vec.at(chunk_id),
                          in_n_hexdump_bytes);
        }
    }
}

void APIDumpPrinter::print_hexdump(FILE*                       in_file_handle,
                                   const std::vector<uint8_t>& in_chunk,
                                   uint32_t                    in_n_bytes_max)
{
    const uint32_t n_bytes_to_print = std::min<uint32_t>(in_n_bytes_max,
                                                         static_cast<uint32_t>(in_chunk.size() ));

    for (uint32_t offset = 0;
                  offset < n_bytes_to_print;
                  offset += 16)
    {
        fprintf(in_file_handle,
                "      +%06x ",
                offset);

        for (uint32_t n = 0; n < 16; ++n)
        {
            if (offset + n < n_bytes_to_print)
            {
                fprintf(in_file_handle,
                        " %02x",
                        in_chunk.at(offset + n) );
            }
            else
            {
                fprintf(in_file_handle,
                        "   ");
            }
        }

        fprintf(in_file_handle,
                "  |");

        for (uint32_t n = 0; n < 16 && offset + n < n_bytes_to_print; ++n)
        {
            const uint8_t c = in_chunk.at(offset + n);

            fprintf(in_file_handle,
                    "%c",
                    (c >= 32 && c < 127) ? c
                                         : '.');
        }

        fprintf(in_file_handle,
                "|\n");
    }

    if (n_bytes_to_print < in_chunk.size() )
    {
        fprintf(in_file_handle,
                "      ... (%u more bytes)\n",
                static_cast<uint32_t>(in_chunk.size() ) - n_bytes_to_print);
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

/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "argument_formatter.h"
#include "value_formatter.h"

bool Capture::APIDumpPrinter::ArgumentFormatter::format_boolean(const APIInterceptor::APIFunctionArgument& in_argument,
                                                                std::string*                               out_text_ptr)
{
    bool result = true;

    /* The flags which the hooks add are unsigned. */
    switch (in_argument.type)
    {
        case APIInterceptor::ARGTYPE_I32:
        {
            *out_text_ptr = ValueFormatter::format_boolean(in_argument.get_i32() );

            break;
        }

        case APIInterceptor::ARGTYPE_U32:
        {
            *out_text_ptr = ValueFormatter::format_boolean(static_cast<int32_t>(in_argument.get_u32() ));

            break;
        }

        default:
        {
            result = false;

            break;
        }
    }

    return result;
}

bool Capture::APIDumpPrinter::ArgumentFormatter::format_chunk(const Capture::APIDumpLoader::Workload&    in_workload,
                                                              const APIInterceptor::APIFunctionArgument& in_argument,
                                                              const FormatChunkFunc&                     in_format_func,
                                                              std::string*                               out_text_ptr)
{
    const Capture::APIDumpLoader::DataChunk* chunk_ptr = nullptr;
    bool                                     result    = false;

    if (in_argument.type != APIInterceptor::ARGTYPE_DATA_CHUNK_ID)
    {
        goto end;
    }

    chunk_ptr = Capture::APIDumpLoader::get_data_chunk_ptr(in_workload,
                                                            in_argument.get_data_chunk_id() );

    if (chunk_ptr == nullptr)
    {
        goto end;
    }

    if (chunk_ptr->empty() )
    {
        *out_text_ptr = "NULL";
        result        = true;
    }
    else
    {
        result = in_format_func(*chunk_ptr,
                                out_text_ptr);
    }

end:
    return result;
}

bool Capture::APIDumpPrinter::ArgumentFormatter::format_i32(const APIInterceptor::APIFunctionArgument& in_argument,
                                                            const FormatI32Func&                       in_format_func,
                                                            std::string*                               out_text_ptr)
{
    const bool result = (in_argument.type == APIInterceptor::ARGTYPE_I32);

    if (result)
    {
        *out_text_ptr = in_format_func(in_argument.get_i32() );
    }

    return result;
}

bool Capture::APIDumpPrinter::ArgumentFormatter::format_pointer(const APIInterceptor::APIFunctionArgument& in_argument,
                                                                const FormatPointerFunc&                   in_format_func,
                                                                std::string*                               out_text_ptr)
{
    const bool result = (in_argument.type == APIInterceptor::ARGTYPE_VOID_PTR);

    if (result)
    {
        *out_text_ptr = in_format_func(in_argument.get_ptr() );
    }

    return result;
}

bool Capture::APIDumpPrinter::ArgumentFormatter::format_pointer_out(const APIInterceptor::APIFunctionArgument& in_argument,
                                                                    const bool&                                in_is_out,
                                                                    const FormatPointerFunc&                   in_format_func,
                                                                    std::string*                               out_text_ptr)
{
    /* Before the call, the argument is the address of the returned pointer. */
    return (in_is_out                                    &&
            format_pointer(in_argument,
                           in_format_func,
                           out_text_ptr) );
}

bool Capture::APIDumpPrinter::ArgumentFormatter::format_u32(const APIInterceptor::APIFunctionArgument& in_argument,
                                                            const FormatU32Func&                       in_format_func,
                                                            std::string*                               out_text_ptr)
{
    const bool result = (in_argument.type == APIInterceptor::ARGTYPE_U32);

    if (result)
    {
        *out_text_ptr = in_format_func(in_argument.get_u32() );
    }

    return result;
}

bool Capture::APIDumpPrinter::ArgumentFormatter::format_u32_after_state(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                                        const uint32_t&                              in_n_argument,
                                                                        const APIInterceptor::APIFunctionArgument&   in_argument,
                                                                        const std::function<std::string(const uint32_t& in_state,
                                                                                                        const uint32_t& in_value)>& in_format_func,
                                                                        std::string*                                 out_text_ptr)
{
    const bool result = (in_argument.type == APIInterceptor::ARGTYPE_U32 &&
                         in_n_argument    != 0);

    if (result)
    {
        /* The state is the argument before the value. */
        *out_text_ptr = in_format_func(in_call.arg_in_vec.at(in_n_argument - 1).get_u32(),
                                       in_argument.get_u32() );
    }

    return result;
}

/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What the decoders of the APIs of Direct3D 7 and 8 do alike when they print an argument: look at the type of the argument, and format it if it
 * is what the kind of the argument says. Which kinds there are, and what each is formatted as, is each decoder's; this is the checking and the
 * handing over of the value.
 */
#ifndef APIDUMPPRINTER_ARGUMENT_FORMATTER_H
#define APIDUMPPRINTER_ARGUMENT_FORMATTER_H

#include "Capture/APIDumpLoader/APIDumpLoader.h"
#include <functional>
#include <string>

namespace Capture
{
    namespace APIDumpPrinter
    {
        class ArgumentFormatter
        {
        public:
            typedef std::function<bool(const Capture::APIDumpLoader::DataChunk& in_chunk,
                                       std::string*                             out_text_ptr)> FormatChunkFunc;
            typedef std::function<std::string(const int32_t& in_value)>                         FormatI32Func;
            typedef std::function<std::string(const void* in_pointer)>                          FormatPointerFunc;
            typedef std::function<std::string(const uint32_t& in_value)>                        FormatU32Func;

            /* A boolean, which is signed, or unsigned when it is one of the flags that the hooks add. Each returns false, and leaves the text as it was, if
             * the argument is of another type.
             */
            static bool format_boolean(const APIInterceptor::APIFunctionArgument& in_argument,
                                       std::string*                               out_text_ptr);

            /* A structure, or a GUID, which the dump holds as a chunk; "NULL" for a pointer that was null. False too if the chunk is not in the dump, or
             * the function does not know what it is.
             */
            static bool format_chunk(const Capture::APIDumpLoader::Workload&    in_workload,
                                     const APIInterceptor::APIFunctionArgument& in_argument,
                                     const FormatChunkFunc&                     in_format_func,
                                     std::string*                               out_text_ptr);

            static bool format_i32(const APIInterceptor::APIFunctionArgument& in_argument,
                                   const FormatI32Func&                       in_format_func,
                                   std::string*                               out_text_ptr);

            /* A pointer to an object of the API. */
            static bool format_pointer(const APIInterceptor::APIFunctionArgument& in_argument,
                                       const FormatPointerFunc&                   in_format_func,
                                       std::string*                               out_text_ptr);

            /* A pointer which the call wrote (an object it made); before the call, the argument is the address of it, and is not formatted. */
            static bool format_pointer_out(const APIInterceptor::APIFunctionArgument& in_argument,
                                           const bool&                                in_is_out,
                                           const FormatPointerFunc&                   in_format_func,
                                           std::string*                               out_text_ptr);

            static bool format_u32(const APIInterceptor::APIFunctionArgument& in_argument,
                                   const FormatU32Func&                       in_format_func,
                                   std::string*                               out_text_ptr);

            /* The value of a render state or of a texture stage state, which is told by the argument before it (the state). */
            static bool format_u32_after_state(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                               const uint32_t&                              in_n_argument,
                                               const APIInterceptor::APIFunctionArgument&   in_argument,
                                               const std::function<std::string(const uint32_t& in_state,
                                                                               const uint32_t& in_value)>& in_format_func,
                                               std::string*                                 out_text_ptr);
        };
    }
}

#endif /* APIDUMPPRINTER_ARGUMENT_FORMATTER_H */

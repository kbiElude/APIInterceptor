/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Prints the arguments of D3D8 calls in a human-readable form: enums and flags by name, structures field by field,
 * objects by a name which identifies them across the dump (e.g. Texture#3).
 */
#ifndef APIDUMPPRINTER_D3D8_DECODER_H
#define APIDUMPPRINTER_D3D8_DECODER_H

#include "capture/api_dump_loader/api_dump_loader.h"
#include "capture/api_dump_loader/object_namer.h"
#include "common/api_function_argument.h"
#include "i_api_decoder.h"
#include "interception/hooks/D3D8/types.h"
#include "types.h"
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

namespace Capture
{
    namespace APIDumpPrinter
    {
        class D3D8Decoder : public IAPIDecoder
        {
        public:
            /* Prints an argument of a D3D8 call. Returns false if the argument is not decoded; the caller then prints it
             * the generic way. in_is_out tells whether the argument comes from the out args of the call.
             */
            bool print_argument(FILE*                                        in_file_handle,
                                const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                const uint32_t&                              in_n_argument,
                                const bool&                                  in_is_out,
                                const APIInterceptor::APIFunctionArgument&   in_argument,
                                const Capture::APIDumpLoader::Workload&      in_workload) const override;

            /* As above, for the returned value. */
            bool print_returned_value(FILE*                                        in_file_handle,
                                      const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                      const APIInterceptor::APIFunctionArgument&   in_returned_value) const override;

            /* Names the objects created by the call. To be called before the call is printed. */
            void forget_released_objects (const Capture::APIDumpLoader::DumpedAPICall& in_call) override;
            void register_created_objects(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                          const Capture::APIDumpLoader::Workload&      in_workload) override;

        private:
            /* Returns "<type>#<n>" if the object has been seen being created, "<type>@0x<address>" otherwise. */
            std::string get_object_name(const void* in_object_ptr,
                                        const char* in_type_name_ptr) const;

            static std::string format_color_value        (const Interception::Hooks::D3D8::D3DCOLORVALUE& in_value);
            static std::string format_enum               (const Interception::Hooks::D3D8::ValueKind&     in_kind,
                                                          const uint32_t&                                 in_value);
            static std::string format_flags              (const Interception::Hooks::D3D8::ValueKind&     in_kind,
                                                          const uint32_t&                                 in_value);
            static std::string format_fvf                (const uint32_t&                                 in_value);
            static std::string format_hresult            (const int32_t&                                  in_value);
            static std::string format_resource_properties(const uint32_t&                                 in_format,
                                                          const uint32_t&                                 in_type,
                                                          const uint32_t&                                 in_usage,
                                                          const uint32_t&                                 in_pool);

            /* Returns false if the structure is not decoded (e.g. the chunk has an unexpected size). */
            static bool format_struct(const Interception::Hooks::D3D8::ValueKind& in_kind,
                                      const std::vector<uint8_t>&                 in_chunk_u8_vec,
                                      std::string*                                out_text_ptr);

            Capture::APIDumpLoader::ObjectNamer m_object_namer;
        };
    }
}

#endif /* APIDUMPPRINTER_D3D8_DECODER_H */

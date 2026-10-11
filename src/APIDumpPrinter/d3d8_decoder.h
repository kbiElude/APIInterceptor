/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Prints the arguments of D3D8 calls in a human-readable form: enums and flags by name, structures field by field,
 * objects by a name which identifies them across the dump (e.g. Texture#3).
 */
#ifndef APIDUMPPRINTER_D3D8_DECODER_H
#define APIDUMPPRINTER_D3D8_DECODER_H

#include "APIDumpLoader/APIDumpLoader.h"
#include "D3D8/types.h"
#include "types.h"
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

namespace APIDumpPrinter
{
    class D3D8Decoder
    {
    public:
        /* Prints an argument of a D3D8 call. Returns false if the argument is not decoded; the caller then prints it
         * the generic way. in_is_out tells whether the argument comes from the out args of the call.
         */
        bool print_argument(FILE*                                      in_file_handle,
                            const APIDumpLoader::DumpedAPICall&        in_call,
                            const uint32_t&                            in_n_argument,
                            const bool&                                in_is_out,
                            const APIInterceptor::APIFunctionArgument& in_argument,
                            const APIDumpLoader::Workload&             in_workload) const;

        /* As above, for the returned value. */
        bool print_returned_value(FILE*                                      in_file_handle,
                                  const APIDumpLoader::DumpedAPICall&        in_call,
                                  const APIInterceptor::APIFunctionArgument& in_returned_value) const;

        /* Names the objects created by the call. To be called before the call is printed. */
        void register_created_objects(const APIDumpLoader::DumpedAPICall& in_call);

    private:
        static std::string format_boolean            (const int32_t&                in_value);
        static std::string format_color              (const uint32_t&               in_value);
        static std::string format_color_value        (const D3D8::D3DCOLORVALUE&    in_value);
        static std::string format_enum               (const D3D8::ValueKind&        in_kind,
                                                      const uint32_t&               in_value);
        static std::string format_flags              (const D3D8::ValueKind&        in_kind,
                                                      const uint32_t&               in_value);
        static std::string format_fvf                (const uint32_t&               in_value);
        static std::string format_hex                (const uint32_t&               in_value);
        static std::string format_hresult            (const int32_t&                in_value);
        static std::string format_resource_properties(const uint32_t&               in_format,
                                                      const uint32_t&               in_type,
                                                      const uint32_t&               in_usage,
                                                      const uint32_t&               in_pool);
        static std::string format_state_value        (const StateValueInfo&         in_info,
                                                      const uint32_t&               in_value);

        /* Returns false if the structure is not decoded (e.g. the chunk has an unexpected size). */
        static bool format_struct(const D3D8::ValueKind&     in_kind,
                                  const std::vector<uint8_t>& in_chunk_u8_vec,
                                  std::string*               out_text_ptr);

        /* Returns "<type>#<n>" if the object has been seen being created, "<type>@0x<address>" otherwise. */
        std::string get_object_name(const void* in_object_ptr,
                                    const char* in_type_name_ptr) const;

        std::map<const void*, std::string> m_object_name_map;
        std::map<std::string, uint32_t>    m_n_created_objects_map; /* by type name */
    };
}

#endif /* APIDUMPPRINTER_D3D8_DECODER_H */

/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Prints the arguments of D3D7 (DirectDraw 7 and Direct3D 7) calls in a human-readable form: enums and flags by name, structures
 * field by field, objects by a name which identifies them across the dump (e.g. Surface#3).
 */
#ifndef APIDUMPPRINTER_D3D7_DECODER_H
#define APIDUMPPRINTER_D3D7_DECODER_H

#include "Capture/APIDumpLoader/APIDumpLoader.h"
#include "d3d7_names.h"
#include "i_api_decoder.h"
#include "Interception/Hooks/D3D7/types.h"
#include "object_namer.h"
#include "types.h"
#include <stdio.h>
#include <string>
#include <vector>

namespace Capture
{
    namespace APIDumpPrinter
    {
        class D3D7Decoder : public IAPIDecoder
        {
        public:
            bool print_argument(FILE*                                        in_file_handle,
                                const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                const uint32_t&                              in_n_argument,
                                const bool&                                  in_is_out,
                                const APIInterceptor::APIFunctionArgument&   in_argument,
                                const Capture::APIDumpLoader::Workload&      in_workload) const override;

            bool print_returned_value(FILE*                                        in_file_handle,
                                      const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                      const APIInterceptor::APIFunctionArgument&   in_returned_value) const override;

            void register_created_objects(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                          const Capture::APIDumpLoader::Workload&      in_workload) override;

        private:
            static std::string format_color_value(const Interception::Hooks::D3D7::D3DCOLORVALUE& in_value);
            static std::string format_enum       (const Interception::Hooks::D3D7::ValueKind&     in_kind,
                                                  const uint32_t&                                 in_value);
            static std::string format_flag_table (const D3D7FlagTable&                            in_table,
                                                  const uint32_t&                                 in_value);
            static std::string format_flags      (const Interception::Hooks::D3D7::ValueKind&     in_kind,
                                                  const uint32_t&                                 in_value);
            static std::string format_four_cc    (const uint32_t&                                 in_value);
            static std::string format_fvf        (const uint32_t&                                 in_value);
            static std::string format_guid       (const GUID&                                     in_value);
            static std::string format_hresult    (const int32_t&                                  in_value);
            static std::string format_pixel_format(const Interception::Hooks::D3D7::DDPIXELFORMAT& in_value);
            static std::string format_surface_caps(const Interception::Hooks::D3D7::DDSCAPS2&     in_value);

            /* Returns false if the structure is not decoded (e.g. the chunk has an unexpected size). */
            static bool format_struct(const Interception::Hooks::D3D7::ValueKind& in_kind,
                                      const std::vector<uint8_t>&                 in_chunk_u8_vec,
                                      std::string*                                out_text_ptr);

            /* Returns the name of the type of the object which a call makes. It is the type of the interface that the call is asked for
             * if the call is QueryInterface or DirectDrawCreateEx, whose argument tells it. Returns nullptr if it is not known.
             */
            static const char* get_created_object_type_name_ptr(const Capture::APIDumpLoader::DumpedAPICall&      in_call,
                                                                const Interception::Hooks::D3D7::ArgumentInfo&    in_info,
                                                                const Capture::APIDumpLoader::Workload&           in_workload);

            ObjectNamer m_object_namer;
        };
    }
}

#endif /* APIDUMPPRINTER_D3D7_DECODER_H */

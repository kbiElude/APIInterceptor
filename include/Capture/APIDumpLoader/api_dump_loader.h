/* API Dumper (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(APIDUMPLOADER_H)
#define APIDUMPLOADER_H

#include "Common/types.h"
#include <array>
#include <functional>
#include <memory>
#include <vector>

namespace Capture
{
    namespace APIDumpLoader
    {
        /* Forward decls */
        typedef struct DumpedAPICall
        {
            std::vector<APIInterceptor::APIFunctionArgument>     arg_in_vec;
            std::vector<APIInterceptor::APIFunctionArgument>     arg_out_vec;
            APIInterceptor::APIFunction                          func               = APIInterceptor::APIFunction::APIFUNCTION_UNKNOWN;
            std::unique_ptr<APIInterceptor::APIFunctionArgument> returned_value_ptr;
            uint32_t                                             thread_id          = 0;
            uint64_t                                             timestamp_qpc      = 0; /* ticks of Workload::qpc_frequency */
        } DumpedAPICall;

        typedef struct DumpedSurface
        {
            std::vector<uint8_t>    data_u8_vec;
            std::array<uint32_t, 2> extents_u32vec2;
        } DumpedSurface;

        /* Whether the data chunks that a call refers to are wanted: asked with the call and the number of the frame it is in (see is_frame_boundary()). */
        typedef std::function<bool(const DumpedAPICall& in_call,
                                   const uint64_t&      in_frame_index)> ChunkWantedFunc;

        typedef std::vector<uint8_t>                 DataChunk;
        typedef std::unique_ptr<DataChunk>           DataChunkUniquePtr;
        typedef std::vector<DumpedAPICall>           DumpedAPICallVector;
        typedef std::unique_ptr<DumpedAPICallVector> DumpedAPICallVectorUniquePtr;
        typedef std::vector<DumpedSurface>           DumpedSurfaceVector;
        typedef std::unique_ptr<DumpedSurfaceVector> DumpedSurfaceVectorUniquePtr;

        typedef struct Workload
        {
            std::vector<DataChunkUniquePtr> data_chunk_ptr_vec;
            DumpedAPICallVectorUniquePtr    dumped_api_call_vec_ptr;
            DumpedSurfaceVectorUniquePtr    dumped_surface_vec_ptr;
            uint32_t                        first_data_chunk_id = 0; /* data_chunk_ptr_vec[0] has this ID in the dump */
            uint64_t                        file_offset_n_bytes = 0; /* of the frame of the file which holds the segment, if it was read from a file (see WorkloadReader) */
            uint64_t                        n_compressed_bytes  = 0; /* of that frame                                                                                    */
            uint32_t                        pointer_n_bytes     = 0; /* of the process which was dumped              */
            uint64_t                        qpc_frequency       = 0; /* ticks per second                             */

        } Workload;

        typedef std::unique_ptr<Workload> WorkloadUniquePtr;


        /* Loads the whole file into one workload. Use WorkloadReader for dumps which are too big for that. */
        WorkloadUniquePtr create_workload_from_file(const char* in_filename_ptr);

        /* Returns nullptr for a data chunk which is not part of the workload. A dump read in segments (see
         * WorkloadReader) holds the chunks of one segment at a time.
         */
        const DataChunk* get_data_chunk_ptr(const Workload& in_workload,
                                            const uint32_t& in_data_chunk_id);
    }
}

#endif /* APIDUMPLOADER_H */

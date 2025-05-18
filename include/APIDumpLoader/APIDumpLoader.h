/* API Dumper (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(APIDUMPLOADER_H)
#define APIDUMPLOADER_H

#include "Common/types.h"
#include <array>
#include <memory>
#include <vector>

namespace APIDumpLoader
{
    /* Forward decls */
    typedef struct DumpedAPICall
    {
        std::vector<APIInterceptor::APIFunctionArgument>     arg_vec;
        APIInterceptor::APIFunction                          func               = APIInterceptor::APIFunction::APIFUNCTION_UNKNOWN;
        std::unique_ptr<APIInterceptor::APIFunctionArgument> returned_value_ptr;
    } DumpedAPICall;

    typedef struct DumpedSurface
    {
        std::vector<uint8_t>    data_u8_vec;
        std::array<uint32_t, 2> extents;
    };

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

    } Workload;

    typedef std::unique_ptr<Workload> WorkloadUniquePtr;

    WorkloadUniquePtr create_workload_from_file(const char* in_filename_ptr);
}

#endif /* APIDUMPLOADER_H */
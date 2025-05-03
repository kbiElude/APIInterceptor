/* API Dumper (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(APIDUMPLOADER_H)
#define APIDUMPLOADER_H

#include "Common/types.h"
#include <memory>
#include <vector>

namespace APIDumpLoader
{
    /* Forward decls */
    typedef struct DumpedAPICall
    {
        std::vector<APIInterceptor::APIFunctionArgument>     arg_vec;
        APIInterceptor::APIFunction                          func           = APIInterceptor::APIFunction::APIFUNCTION_UNKNOWN;
        std::unique_ptr<APIInterceptor::APIFunctionArgument> returned_value;
    } DumpedAPICall;

    typedef std::vector<DumpedAPICall>           DumpedAPICallVector;
    typedef std::unique_ptr<DumpedAPICallVector> DumpedAPICallVectorUniquePtr;

    DumpedAPICallVectorUniquePtr create_dumped_api_call_vec_from_file(const char* in_filename_ptr);
}

#endif /* APIDUMPLOADER_H */
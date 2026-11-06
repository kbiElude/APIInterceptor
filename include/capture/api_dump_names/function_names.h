/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The names of the API functions that a workload has calls of: for the tools which say what a call is.
 */
#ifndef APIDUMPNAMES_FUNCTION_NAMES_H
#define APIDUMPNAMES_FUNCTION_NAMES_H

#include "common/types.h"

namespace Capture
{
    namespace APIDumpNames
    {
        /* Returns "?!" for functions that are not recognized. */
        const char* get_function_name(const APIInterceptor::APIFunction& in_function);
    }
}

#endif /* APIDUMPNAMES_FUNCTION_NAMES_H */

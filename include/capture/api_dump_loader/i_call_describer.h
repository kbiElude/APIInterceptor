/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Says what the calls of one API do to the frames a replay makes (see CallClass).
 */
#ifndef APIDUMPLOADER_I_CALL_DESCRIBER_H
#define APIDUMPLOADER_I_CALL_DESCRIBER_H

#include "capture/api_dump_loader/api_dump_loader.h"
#include "capture/api_dump_loader/types.h"

namespace Capture
{
    namespace APIDumpLoader
    {
        class ICallDescriber
        {
        public:
            virtual ~ICallDescriber() = default;

            /* Calls come in the order they were made: the answer may depend on the calls before. */
            virtual CallClass describe(const DumpedAPICall& in_call) = 0;

            virtual APIGroup get_group() const = 0;
        };
    }
}

#endif /* APIDUMPLOADER_I_CALL_DESCRIBER_H */

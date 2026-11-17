/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Describes the calls of Direct3D 7.
 */
#ifndef APIDUMPLOADER_D3D7_CALL_DESCRIBER_H
#define APIDUMPLOADER_D3D7_CALL_DESCRIBER_H

#include "capture/api_dump_loader/i_call_describer.h"

namespace Capture
{
    namespace APIDumpLoader
    {
        class D3D7CallDescriber : public ICallDescriber
        {
        public:
            CallClass describe(const DumpedAPICall& in_call) override;
            APIGroup  get_group() const override;

            /* The class of the function alone. */
            static CallClass get_function_class(const APIInterceptor::APIFunction& in_function);
        };
    }
}

#endif /* APIDUMPLOADER_D3D7_CALL_DESCRIBER_H */

/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The describers of all APIs, asked as one: a call goes to the describer of its API. Calls of other APIs are state.
 *
 * Use one set for each walk over the calls, in order.
 */
#ifndef APIDUMPLOADER_CALL_DESCRIBER_SET_H
#define APIDUMPLOADER_CALL_DESCRIBER_SET_H

#include "capture/api_dump_loader/i_call_describer.h"
#include <memory>
#include <vector>

namespace Capture
{
    namespace APIDumpLoader
    {
        class CallDescriberSet
        {
        public:
            CallDescriberSet();

            /* Calls come in the order they were made. */
            CallClass describe(const DumpedAPICall& in_call);

            /* The class of the function alone. */
            static CallClass get_function_class(const APIInterceptor::APIFunction& in_function);

        private:
            std::vector<std::unique_ptr<ICallDescriber> > m_describer_ptr_vec;
        };
    }
}

#endif /* APIDUMPLOADER_CALL_DESCRIBER_SET_H */

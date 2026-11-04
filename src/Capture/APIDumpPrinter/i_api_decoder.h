/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What the printer asks of the decoder of an API, which prints the arguments of its calls in a human-readable form.
 */
#ifndef APIDUMPPRINTER_I_API_DECODER_H
#define APIDUMPPRINTER_I_API_DECODER_H

#include "Capture/APIDumpLoader/APIDumpLoader.h"
#include <stdio.h>

namespace Capture
{
    namespace APIDumpPrinter
    {
        class IAPIDecoder
        {
        public:
            virtual ~IAPIDecoder() = default;

            /* Prints an argument of a call of the API. Returns false if the argument is not decoded; the caller then prints it the
             * generic way. in_is_out tells whether the argument comes from the out args of the call.
             */
            virtual bool print_argument(FILE*                                        in_file_handle,
                                        const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                        const uint32_t&                              in_n_argument,
                                        const bool&                                  in_is_out,
                                        const APIInterceptor::APIFunctionArgument&   in_argument,
                                        const Capture::APIDumpLoader::Workload&      in_workload) const = 0;

            /* As above, for the returned value. */
            virtual bool print_returned_value(FILE*                                        in_file_handle,
                                              const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                              const APIInterceptor::APIFunctionArgument&   in_returned_value) const = 0;

            /* Forgets the names of the objects that the call released for the last time, so that the address may name another object. To be
             * called after the call is printed.
             */
            virtual void forget_released_objects(const Capture::APIDumpLoader::DumpedAPICall& in_call) = 0;

            /* Names the objects created by the call. To be called before the call is printed. */
            virtual void register_created_objects(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                  const Capture::APIDumpLoader::Workload&      in_workload) = 0;
        };
    }
}

#endif /* APIDUMPPRINTER_I_API_DECODER_H */

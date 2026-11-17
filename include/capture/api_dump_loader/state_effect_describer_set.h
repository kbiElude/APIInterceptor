/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The state effect describers of all the APIs a workload can hold, asked as one: a call goes to the describer of its API. A call of an API that
 * has no describer ends the process.
 *
 * A set follows one walk over the calls of a workload, in order; use one set for each walk.
 */
#ifndef APIDUMPLOADER_STATE_EFFECT_DESCRIBER_SET_H
#define APIDUMPLOADER_STATE_EFFECT_DESCRIBER_SET_H

#include "capture/api_dump_loader/i_state_effect_describer.h"
#include <memory>
#include <vector>

namespace Capture
{
    namespace APIDumpLoader
    {
        class StateEffectDescriberSet
        {
        public:
            StateEffectDescriberSet();

            /* Calls come in the order they were made. */
            StateEffect describe(const DumpedAPICall& in_call);

        private:
            std::vector<std::unique_ptr<IStateEffectDescriber> > m_describer_ptr_vec;
        };
    }
}

#endif /* APIDUMPLOADER_STATE_EFFECT_DESCRIBER_SET_H */

/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * For an API whose calls are not coalesced (Direct3D 7 and 8 for now): every call is a barrier, so it is made as it was. The API is
 * named on purpose, so that an API that nobody described still ends the process.
 */
#ifndef APIDUMPLOADER_VERBATIM_STATE_EFFECT_DESCRIBER_H
#define APIDUMPLOADER_VERBATIM_STATE_EFFECT_DESCRIBER_H

#include "capture/api_dump_loader/i_state_effect_describer.h"

namespace Capture
{
    namespace APIDumpLoader
    {
        class VerbatimStateEffectDescriber : public IStateEffectDescriber
        {
        public:
            /* The group is D3D7 or D3D8. */
            explicit VerbatimStateEffectDescriber(const APIGroup& in_group);

            StateEffect describe  (const DumpedAPICall& in_call) override;
            APIGroup    get_group () const override;

        private:
            APIGroup m_group;
        };
    }
}

#endif /* APIDUMPLOADER_VERBATIM_STATE_EFFECT_DESCRIBER_H */

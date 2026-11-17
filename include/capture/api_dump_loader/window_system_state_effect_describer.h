/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * For GDI32, USER32 and WGL: windows, device contexts, pixel formats, buffer swaps and OpenGL contexts. Every call is a barrier, because a
 * context or a window decides which state the calls around it act on.
 */
#ifndef APIDUMPLOADER_WINDOW_SYSTEM_STATE_EFFECT_DESCRIBER_H
#define APIDUMPLOADER_WINDOW_SYSTEM_STATE_EFFECT_DESCRIBER_H

#include "capture/api_dump_loader/i_state_effect_describer.h"

namespace Capture
{
    namespace APIDumpLoader
    {
        class WindowSystemStateEffectDescriber : public IStateEffectDescriber
        {
        public:
            /* The group is GDI32, USER32 or WGL. */
            explicit WindowSystemStateEffectDescriber(const APIGroup& in_group);

            StateEffect describe  (const DumpedAPICall& in_call) override;
            APIGroup    get_group () const override;

        private:
            APIGroup m_group;
        };
    }
}

#endif /* APIDUMPLOADER_WINDOW_SYSTEM_STATE_EFFECT_DESCRIBER_H */

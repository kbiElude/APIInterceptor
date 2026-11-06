/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The restorer of an argument of a replayed call which has nothing to do after the call: what the restorers of the numbers and of the
 * structures that are only read are made on. The context is that of the API (D3D8ReplayContext, GlReplayContext).
 */
#ifndef REPLAYENGINEDLL_PASSIVE_RESTORER_H
#define REPLAYENGINEDLL_PASSIVE_RESTORER_H

#include <stddef.h>

namespace Replay
{
    namespace ReplayEngineDLL
    {
        /* The restorers which have nothing to do after the call. */
        template<typename Context>
        class PassiveRestorer
        {
        public:
            void finish(Context*      in_context_ptr,
                        const size_t& in_n_argument,
                        const bool&   in_is_success)
            {
                (void) in_context_ptr;
                (void) in_n_argument;
                (void) in_is_success;
            }
        };
    }
}

#endif /* REPLAYENGINEDLL_PASSIVE_RESTORER_H */

/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The DLL exports plain C functions (their names are not decorated, whatever the namespace); the interfaces are C++ classes, so the DLL and its users must be built with the
 * same compiler and runtime.
 */
#ifndef REPLAYENGINEDLL_ENTRYPOINTS_H
#define REPLAYENGINEDLL_ENTRYPOINTS_H

#include "Replay/ReplayEngineDLL/export.h"
#include "Replay/ReplayEngineDLL/i_replay_engine.h"

namespace Replay
{
    namespace ReplayEngineDLL
    {
        extern "C"
        {
            REPLAYENGINEDLL_API IReplayEngine* aiCreateReplayEngine ();
            REPLAYENGINEDLL_API void           aiDestroyReplayEngine(IReplayEngine* in_engine_ptr);
        }
    }
}

#endif /* REPLAYENGINEDLL_ENTRYPOINTS_H */

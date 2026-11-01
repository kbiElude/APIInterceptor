/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Replay/ReplayEngineDLL/entrypoints.h"
#include "replay_engine.h"

APIDumpReplayer::IReplayEngine* APIDumpReplayer::aiCreateReplayEngine()
{
    return new ReplayEngine();
}

void APIDumpReplayer::aiDestroyReplayEngine(IReplayEngine* in_engine_ptr)
{
    delete in_engine_ptr;
}

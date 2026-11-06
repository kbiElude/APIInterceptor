/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "replay/replay_engine_dll/entrypoints.h"
#include "replay_engine.h"

Replay::ReplayEngineDLL::IReplayEngine* Replay::ReplayEngineDLL::aiCreateReplayEngine()
{
    return new ReplayEngine();
}

void Replay::ReplayEngineDLL::aiDestroyReplayEngine(IReplayEngine* in_engine_ptr)
{
    delete in_engine_ptr;
}

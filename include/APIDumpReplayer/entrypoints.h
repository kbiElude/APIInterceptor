/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The DLL exports plain C functions (their names are not decorated, whatever the namespace); the interfaces are C++ classes, so the DLL and its users must be built with the
 * same compiler and runtime.
 */
#ifndef APIDUMPREPLAYER_ENTRYPOINTS_H
#define APIDUMPREPLAYER_ENTRYPOINTS_H

#include "APIDumpReplayer/export.h"
#include "APIDumpReplayer/i_replay_engine.h"

namespace APIDumpReplayer
{
    extern "C"
    {
        APIDUMPREPLAYER_API IReplayEngine* aiCreateReplayEngine ();
        APIDUMPREPLAYER_API void           aiDestroyReplayEngine(IReplayEngine* in_engine_ptr);
    }
}

#endif /* APIDUMPREPLAYER_ENTRYPOINTS_H */

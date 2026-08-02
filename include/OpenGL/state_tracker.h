/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(AI_STATE_TRACKER_H)
#define AI_STATE_TRACKER_H

#include "OpenGL/types.h"

namespace OpenGL
{
    ContextState& get_context_state   ();
    void          on_context_destroyed(const HGLRC& in_hglrc);
}

#endif /* AI_STATE_TRACKER_H */

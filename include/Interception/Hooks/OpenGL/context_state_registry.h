/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef OPENGL_CONTEXT_STATE_REGISTRY_H
#define OPENGL_CONTEXT_STATE_REGISTRY_H

#include "Interception/Hooks/OpenGL/types.h"
#include <mutex>
#include <unordered_map>

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            /* The state that is tracked for each OpenGL context of the process, made when the context is first used. Any thread. */
            class ContextStateRegistry
            {
            public:
                /* The state of the context; made if there is none yet. */
                ContextState& get_context_state(const HGLRC& in_hglrc);

                void on_context_destroyed(const HGLRC& in_hglrc);

                static ContextStateRegistry* get_ptr();

            private:
                /* The states and the mutex that guards them. */
                struct Contexts
                {
                    std::unordered_map<HGLRC, ContextStateUniquePtr> context_state_map;
                    std::mutex                                       mutex;
                };

                Contexts m_contexts;
            };
        }
    }
}

#endif /* OPENGL_CONTEXT_STATE_REGISTRY_H */

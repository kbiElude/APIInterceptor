/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/hooks/OpenGL/context_state_registry.h"

Interception::Hooks::OpenGL::ContextState& Interception::Hooks::OpenGL::ContextStateRegistry::get_context_state(const HGLRC& in_hglrc)
{
    std::lock_guard<std::mutex> lock(m_contexts.mutex);

    auto& context_state_ptr = m_contexts.context_state_map[in_hglrc];

    if (context_state_ptr == nullptr)
    {
        context_state_ptr.reset(new ContextState() );
    }

    return *context_state_ptr;
}

Interception::Hooks::OpenGL::ContextStateRegistry* Interception::Hooks::OpenGL::ContextStateRegistry::get_ptr()
{
    /* Never destroyed: hooks can still run during shutdown. */
    static ContextStateRegistry* instance_ptr = new ContextStateRegistry();

    return instance_ptr;
}

void Interception::Hooks::OpenGL::ContextStateRegistry::on_context_destroyed(const HGLRC& in_hglrc)
{
    std::lock_guard<std::mutex> lock(m_contexts.mutex);

    m_contexts.context_state_map.erase(in_hglrc);
}

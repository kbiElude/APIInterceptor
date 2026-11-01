/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/globals.h"
#include "Interception/Hooks/OpenGL/state_tracker.h"
#include "Interception/Hooks/WGL/globals.h"

namespace
{
    std::unordered_map<HGLRC, Interception::Hooks::OpenGL::ContextStateUniquePtr> g_context_state_map;
    std::mutex                                                                    g_mutex;
}

Interception::Hooks::OpenGL::ContextState& Interception::Hooks::OpenGL::get_context_state()
{
    const auto hglrc = reinterpret_cast<Interception::Hooks::WGL::PFNWGLGETCURRENTCONTEXTPROC>(Interception::Hooks::WGL::g_cached_get_current_context_func_ptr)();

    AI_ASSERT(hglrc != nullptr);

    {
        std::lock_guard<std::mutex> lock(g_mutex);

        auto& context_state_ptr = g_context_state_map[hglrc];

        if (context_state_ptr == nullptr)
        {
            context_state_ptr.reset(new ContextState() );
        }

        return *context_state_ptr;
    }
}

void Interception::Hooks::OpenGL::on_context_destroyed(const HGLRC& in_hglrc)
{
    {
        std::lock_guard<std::mutex> lock(g_mutex);

        g_context_state_map.erase(in_hglrc);
    }
}

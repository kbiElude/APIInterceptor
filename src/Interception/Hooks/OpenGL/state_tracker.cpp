/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/globals.h"
#include "Interception/Hooks/OpenGL/context_state_registry.h"
#include "Interception/Hooks/OpenGL/state_tracker.h"
#include "Interception/Hooks/WGL/globals.h"

Interception::Hooks::OpenGL::ContextState& Interception::Hooks::OpenGL::get_context_state()
{
    const auto hglrc = reinterpret_cast<Interception::Hooks::WGL::PFNWGLGETCURRENTCONTEXTPROC>(Interception::Hooks::WGL::g_cached_get_current_context_func_ptr)();

    AI_ASSERT(hglrc != nullptr);

    return ContextStateRegistry::get_ptr()->get_context_state(hglrc);
}

void Interception::Hooks::OpenGL::on_context_destroyed(const HGLRC& in_hglrc)
{
    ContextStateRegistry::get_ptr()->on_context_destroyed(in_hglrc);
}

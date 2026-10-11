/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/globals.h"
#include "OpenGL/state_tracker.h"
#include "WGL/globals.h"
#include <cstring>

namespace
{
    std::unordered_map<HGLRC, OpenGL::ContextStateUniquePtr> g_context_state_map;
    std::mutex                                               g_mutex;
}

OpenGL::ContextState::ContextState()
{
    memset(bound_buffers,
           0,
           sizeof(bound_buffers) );

    memset(bound_textures,
           0,
           sizeof(bound_textures) );
}

OpenGL::TextureLevelProps OpenGL::ContextState::get_texture_level_props(GLuint in_texture_id,
                                                                        GLint  in_level) const
{
    const uint64_t key = (static_cast<uint64_t>(in_texture_id) << 16) |
                          static_cast<uint64_t>(in_level);
    const auto     it  = texture_level_props_map.find(key);

    if (it != texture_level_props_map.end() )
    {
        return it->second;
    }

    return TextureLevelProps{};
}

void OpenGL::ContextState::set_texture_level_props(GLuint   in_texture_id,
                                                   GLint    in_level,
                                                   uint32_t in_width,
                                                   uint32_t in_height,
                                                   uint32_t in_depth)
{
    const uint64_t key = (static_cast<uint64_t>(in_texture_id) << 16) |
                          static_cast<uint64_t>(in_level);

    texture_level_props_map[key] = {in_width,
                                    in_height,
                                    in_depth};
}


OpenGL::ContextState& OpenGL::get_context_state()
{
    const auto hglrc = reinterpret_cast<WGL::PFNWGLGETCURRENTCONTEXTPROC>(WGL::g_cached_get_current_context_func_ptr)();

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

void OpenGL::on_context_destroyed(const HGLRC& in_hglrc)
{
    {
        std::lock_guard<std::mutex> lock(g_mutex);

        g_context_state_map.erase(in_hglrc);
    }
}

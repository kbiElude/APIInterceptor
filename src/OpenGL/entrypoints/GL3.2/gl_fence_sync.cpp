/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.2/gl_fence_sync.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

GLsync AI_APIENTRY OpenGL::aiFenceSync(GLenum     condition,
                                       GLbitfield flags)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glFenceSync(condition=[%s] flags=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(condition),
             OpenGL::Utils::get_raw_string_for_gl_bitfield(OpenGL::BitfieldType::Sync_Condition_Mask, flags) );

    if (OpenGL::g_cached_gl_fence_sync == nullptr)
    {
        OpenGL::g_cached_gl_fence_sync = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glFenceSync");
    }

    return reinterpret_cast<PFNGLFENCESYNCPROC>(OpenGL::g_cached_gl_fence_sync)(condition,
                                                                                flags);
}
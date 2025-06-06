/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.2/gl_client_wait_sync.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

GLenum AI_APIENTRY OpenGL::aiClientWaitSync(GLsync     sync,
                                            GLbitfield flags,
                                            GLuint64   timeout)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glClientWaitSync(sync=[%p] flags=[%s] timeout=[%d])",
             sync,
             OpenGL::Utils::get_raw_string_for_gl_bitfield(OpenGL::BitfieldType::Wait_Sync_Mask, flags),
             static_cast<uint32_t>(timeout) );

    return reinterpret_cast<PFNGLCLIENTWAITSYNCPROC>(OpenGL::g_cached_gl_client_wait_sync)(sync,
                                                                                           flags,
                                                                                           timeout);
}
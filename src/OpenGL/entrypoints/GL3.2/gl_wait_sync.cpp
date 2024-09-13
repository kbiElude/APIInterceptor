/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.2/gl_wait_sync.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiWaitSync(GLsync     sync,
                                    GLbitfield flags,
                                    GLuint64   timeout)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glWaitSync(sync=[%p] flags=[%d] timeout=[%lld])",
             sync,
             flags,
             timeout);

    reinterpret_cast<PFNGLWAITSYNCPROC>(OpenGL::g_cached_gl_wait_sync)(sync,
                                                                       flags,
                                                                       timeout);
}
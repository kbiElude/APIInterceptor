/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.2/gl_delete_sync.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDeleteSync(GLsync sync)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glDeleteSync(sync=[%p])",
             sync);

    reinterpret_cast<PFNGLDELETESYNCPROC>(OpenGL::g_cached_gl_delete_sync)(sync);
}
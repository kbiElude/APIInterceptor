/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.2/gl_is_sync.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsSync(GLsync sync)
{
    AI_TRACE("glIsSync(sync=[%p])",
             sync);

    if (OpenGL::g_cached_gl_is_sync == nullptr)
    {
        OpenGL::g_cached_gl_is_sync = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glIsSync");
    }

    return reinterpret_cast<PFNGLISSYNCPROC>(OpenGL::g_cached_gl_is_sync)(sync);
}